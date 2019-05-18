const readline = require('readline');
const {spawn} = require('child_process');
//const wingston = require('winston');
const printf = require('printf');
const socketIo = require('socket.io');

/*
  global variables
*/

let CONFIG = require('./server-config.json');
let clientSide = null;
let gameLogicEngine = null;

/* 
  init command line
*/

// config command line mode
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  prompt: 'ACG>',
  completer: (input) => {
    const keyWords = Object.keys(commands).sort();
    const hits = keyWords.filter((key) => key.startsWith(input));
    return [hits.length ? hits : keyWords, input];
  }
});

// commands and their handler
const commands = {
  'help': {
    alias: 'h',
    description: 'List all commands and their descriptions.',
    handler: commandHelp
  },

  'quit': {
    alias: 'q',
    description: 'Terminate all servers and exit this command line.',
    handler: commandQuit
  },

  'cls': {
    description: 'Clear screen.',
    handler: commandCls
  },

  'loadConfig': {
    alias: 'lc',
    description: 'Reload config file.',
    handler: commandLoadConfig
  },

  'initClientSide': {
    alias: 'ic',
    description: 'Init the Client Side server.',
    handler: commandInitClientSide
  },

  'stopClientSide': {
    alias: 'sc',
    description: 'Stop the Client Side server.',
    handler: commandStopClientSide
  },

  'initGameLogicEngine': {
    alias: 'ig',
    description: 'Run Game Logic Engine in new child process.',
    handler: commandInitGameLogicEngine
  },

  'stopGameLogicEngine': {
    alias: 'sg',
    description: 'Stop the Game Logic Engine.',
    handler: commandStopGameLogicEngine
  },

  'sendMessage': {
    alias: 'm',
    description: 'Send message to given target: [g]: Game Logic Engine',
    handler: commandSendMessage
  }
}

// initial text
console.log('+-------------------------------+\n' + 
            '|        ACG Game Server        |\n' +
            '+-------------------------------+\n' +
            'type \'help\' to list all commands.');
rl.prompt(true);

// listen to command line
rl.on('line', (input) => {
  input = input.trim();
  const command = input.split(' ')[0];

  let aliases = {};
  for (const fullName in commands) {
    if (commands[fullName].alias)
      aliases[commands[fullName].alias] = fullName;
  }

  if (commands[command]) {
    commands[command].handler(input, rl);
  } else if (aliases[command]) {
    commands[aliases[command]].handler(input, rl);
  } else if(input.length === 0) {
    // do nothing
  } else {
    console.log(`unknow command: \'${input}\'`);
  }

  rl.prompt(true);
});

/*
  command line functinos
*/

// exit this console
function commandQuit(input, rl) {
  rl.close();
  process.exit();
}

// clear console screen
function commandCls() {
  readline.cursorTo(process.stdout, 0, 0);
  readline.clearScreenDown(process.stdout);
}

// show command line help
function commandHelp() {
  const formatString = '  %-20s  %-5s  %s';
  console.log(printf(formatString, 'command', 'alias', 'description'));
  console.log('------------------------------------------------------------');

  Object.keys(commands).sort().forEach((command) => {
    console.log(printf(formatString,
                       command,
                       commands[command].alias || '',
                       commands[command].description));
  });
}

// load config file from disk
function commandLoadConfig() {
  CONFIG = require('./server-config.json');
  console.log('config loadded from \'./server-config.json\'');
}

// init socket.io server
function commandInitClientSide() {
  console.log('init Client Side server...');

  if (clientSide) {
    console.error('Client Side server is already running.');
    return;
  }

  clientSide = new ClientSide();
}

// stop socket.io server
function commandStopClientSide() {
  if (!clientSide) {
    console.error('Client Side server isn\'t running.');
    return;
  }

  console.log('Stopping Client Side server...');

  clientSide.stop(() => {
    clientSide = null;
  });
}

// init Game Logic Engine
function commandInitGameLogicEngine() {
  if (gameLogicEngine) {
    console.error(`Game Logic Engine is already running with pid ${gameLogicEngine.getPid()}.`);
    return;
  }

  console.log('init Game Logic Engine.');
  gameLogicEngine = new GameLogicEngine();
}

// stop the Game Logic Engine
function commandStopGameLogicEngine() {
  if (!gameLogicEngine) {
    console.error('Game Logic Engine isn\'t running.');
    return;
  }

  console.log('Stopping Game Logic Engine...');
  gameLogicEngine.stop(() => {
    gameLogicEngine = null;
  });
}

// send message to a target
function commandSendMessage(input) {
  const target = input.split(' ')[1];
  const message = input.substr(input.indexOf(' ', input.indexOf(' ') + 1) + 1);

  if (target === 'g') {
    if (gameLogicEngine) {
      gameLogicEngine.send(message);
    } else {
      console.error('Game Logic Engine isn\'t running.');
    }
  } else {
    console.error('unknow target.');
  }
}

/*
  utility classes and functions
*/

class GameLogicEngine {
  constructor() {
    // properties
    this.processPath = CONFIG.game_logic_engine_path;
    this._handlers = {};

    // bind functions to 'this'
    this.getPid = this.getPid.bind(this);
    this.on = this.on.bind(this);
    this.send = this.send.bind(this);
    this._defaultOnDataHandler = this._defaultOnDataHandler.bind(this);
    this._defaultOnStderrHandler = this._defaultOnStderrHandler.bind(this);

    // create Game Logic Engine process
    this.process = spawn(this.processPath);

    // listen to the events of the process
    this.process.on('close', () => {
      console.log(`[GameLogicEngine]: server is stop.`);
      if (this._handlers.close)
        this._handlers.close();
    });

    this.process.on('error', () => {
      console.error('[GameLogicEngine]: some error occured.');
    });

    this.process.stdout.on('data', (data) => {
      data = data.toString().trim();
      (this._handlers.data || this._defaultOnDataHandler)(data);
    });

    this.process.stderr.on('data', (data) => {
      data = data.toString().trim();
      (this._handlers.stderr || this._defaultOnStderrHandler)(data);
    });
    
    console.log(`[GameLogicEngine]: server runs with pid ${this.getPid()}.`);
  }

  getPid() {
    return this.process.pid;
  }

  stop(callback) {
    this._handlers.close = callback;
    this.process.kill();
  }

  on(event, callback) {
    this._handlers[event] = callback;
  }

  send(data) {
    this.process.stdin.write(`${data}\n`);
  }

  _defaultOnDataHandler(data) {
    console.log(`[GameLogicEngine]: data >>>${data}<<<`);
  }

  _defaultOnStderrHandler(data) {
    console.log(`[GameLogicEngine]: stderr >>>${data}<<<`);
  }
}

class ClientSide {
  constructor(options) {
    // properties
    this.socketIoPort = CONFIG.socket_server_port;
    this.ioServer = null;

    // create socket.io server
    const io = socketIo(this.socketIoPort);
    this.ioServer = io;

    // listen to events of the socket.io server
    io.sockets.on('connection', (client) => {
      console.log(`[ClientSide]: client connected.`);

      client.on('sendData', (data) => {
        console.log(`[ClientSide]: data from '${client.id}': >>>'${JSON.stringify(data, null, 2)}'<<<`);
        client.broadcast.to(client.id).emit('sendData', data);
      });
    });

    console.log(`[ClientSide]: server runs at port ${CONFIG.socket_server_port}.`);
  }

  stop(callback) {
    this.ioServer.close(() => {
      this.ioServer = null;
      console.log('[ClientSide]: server is stop.');
      callback();
    });
  }
}
