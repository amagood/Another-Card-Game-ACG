const readline = require('readline');
const socketIo = require('socket.io');
const {spawn} = require('child_process');
const path = require('path');
const printf = require('printf');
const colors = require('colors');
const ConnectionManager = require('./connection-manager');

colors.setTheme({
  silly: 'rainbow',
  input: 'grey',
  verbose: 'cyan',
  prompt: 'grey',
  info: 'green',
  data: 'grey',
  help: 'cyan',
  warn: 'yellow',
  debug: 'cyan',
  error: 'red'
});

/*
 * global variables
 */

const configFilePath = './server-config.json';
let CONFIG = require(configFilePath);
let logger = null;

let clientSide = null;
let gameLogicEngine = null;

/*
 * command line functinos
 */

// exit this console
function commandQuit(input, rl) {
  logger.info(`Quit Game server...`);
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
  const commands = gameServer.commandLine.commands;
  const formatString = `  ${`%-20s`.bold}  ${`%-5s`.yellow.bold}  %s`;
  logger.log(printf(formatString, 'command', 'alias', 'description').bold);
  logger.log(`------------------------------------------------------------`);

  Object.keys(commands).sort().forEach((command) => {
    logger.log(printf(formatString,
                      command,
                      commands[command].alias || '',
                      commands[command].description || ''));
  });
}

// load config file from disk
function commandLoadConfig() {
  CONFIG = require(configFilePath);
  logger.log(`config loadded from '${configFilePath}'`);
}

// init client side server
function commandInitClientSide() {
  logger.log(`init Client Side server...`);

  if (clientSide) {
    logger.error(`Client Side server is already running.`);
    return;
  }

  clientSide = new ClientSide({port: CONFIG.socket_server_port});
}

// stop client side server
function commandStopClientSide() {
  if (!clientSide) {
    logger.error(`Client Side server isn't running.`);
    return;
  }

  logger.log(`Stopping Client Side server...`);

  clientSide.stop(() => {
    clientSide = null;
  });
}

// init Game Logic Engine
function commandInitGameLogicEngine() {
  if (gameLogicEngine) {
    logger.error(`Game Logic Engine is already running with pid ${gameLogicEngine.getPid()}.`);
    return;
  }

  logger.log(`init Game Logic Engine...`);
  gameLogicEngine = new GameLogicEngine();
}

// stop the Game Logic Engine
function commandStopGameLogicEngine() {
  if (!gameLogicEngine) {
    logger.error(`Game Logic Engine isn't running.`);
    return;
  }

  logger.log(`Stopping Game Logic Engine...`);
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
      logger.error(`Game Logic Engine isn't running.`);
    }
  } else if (target === 'c') {
    if (clientSide) {
      const id = message.split(' ')[0];
      const data = JSON.parse(message.substr(message.indexOf(' ') + 1));
      clientSide.send(id, data);
      logger.debug(`${id}, ${data}`);
    } else {
      logger.error(`Client Side Server isn't running.`);
    }
  } else {
    logger.error(`unknow target.`);
  }
}

/*
 * utility classes and functions
 */

class GameServer {
  constructor() {
    this.commandLine = new CommandLine();
    commandInitGameLogicEngine();
    commandInitClientSide();
    this.connectionManager = new ConnectionManager({
      clientSide: clientSide,
      serverSide: gameLogicEngine,
      logger: logger
    });
  }
}

class Logger {
  constructor(options = {}) {
    this.console = options.console || console;
  }

  dir(obj) {
    this.console.dir(obj);
  }

  log(str) {
    this.console.log(str.toString());
  }

  debug(str) {
    this.console.debug(`${`DEBUG`.inverse} ${str.toString()}`.debug.bold);
  }

  info(str) {
    this.console.info(`${`INFO`.inverse} ${str.toString()}`.info.bold);
  }

  warn(str) {
    this.console.warn(`${`WARN`.inverse} ${str.toString()}`.warn.bold);
  }

  error(str) {
    this.console.error(`${`ERROR`.inverse} ${str.toString()}`.error.bold);
  }
}

class CommandLine {
  constructor() {
    
    // commands and their handler
    this.commands = {
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
        description: 'Send message to: [g] Game Logic Engine, [c] Client Side',
        handler: commandSendMessage
      }
    };

    // config command line mode
    this.rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
      prompt: 'ACG>'.prompt,
      completer: (input) => {
        const keyWords = Object.keys(this.commands).sort();
        const hits = keyWords.filter((key) => key.startsWith(input));
        return [hits.length ? hits : keyWords, input];
      }
    });
    
    // initial text
    logger.log((`+-------------------------------+\n` + 
                `|        ACG Game Server        |\n` +
                `+-------------------------------+\n`).rainbow.bgWhite +
                `type '${`help`.yellow.bold}' to list all commands.`);
    this.rl.prompt(true);

    // listen to command line
    this.rl.on('line', (input) => {
      input = input.trim();
      const command = input.split(' ')[0];

      // make alias
      const aliases = {};
      for (const fullName in this.commands) {
        if (this.commands[fullName].alias)
          aliases[this.commands[fullName].alias] = fullName;
      }

      // try to match command
      if (this.commands[command]) {
        this.commands[command].handler(input, this.rl);
      } else if (aliases[command]) {
        this.commands[aliases[command]].handler(input, this.rl);
      } else if(input.length === 0) {
        // press enter, do nothing
      } else {
        logger.error(`unknow command: '${input}'`);
      }

      this.rl.prompt(true);
    });
  }
}

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
    this.process = spawn(this.processPath, [], {
      cwd: path.dirname(this.processPath)
    });

    // listen to the events of the process
    this.process.on('close', () => {
      logger.info(`[GameLogicEngine]: server is stop.`);
      if (this._handlers.close)
        this._handlers.close();
    });

    this.process.on('error', () => {
      logger.error(`[GameLogicEngine]: some error occured.`);
    });

    this.process.stdout.on('data', (data) => {
      data = data.toString().trim();
      data = JSON.parse(data);
      (this._handlers.data || this._defaultOnDataHandler)(data);
    });

    this.process.stderr.on('data', (data) => {
      data = data.toString().trim();
      (this._handlers.stderr || this._defaultOnStderrHandler)(data);
    });
    
    logger.info(`[GameLogicEngine]: server runs with pid ${this.getPid()}.`);
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

  onData(handler) {
    this.on('data', handler);
  }

  send(data) {
    // convert data to string
    if (typeof data === 'object')
      data = JSON.stringify(data);
    else
      data = data.toString();

    this.process.stdin.write(`${data}\n`);
    logger.debug(`to server:\n${data}`);
  }

  _defaultOnDataHandler(data) {
    logger.log(`[GameLogicEngine]: data:\n>>>${data}<<<`);
  }

  _defaultOnStderrHandler(data) {
    logger.warn(`[GameLogicEngine]: stderr:\n>>>${data}<<<`);
  }
}

class ClientSide {
  constructor(options) {
    // properties
    this.socketIoPort = options.port;
    this.ioServer = null;
    this.clientPacketHandler = null;
    this.clientDisconnectHandler = null;

    // create socket.io server
    const io = socketIo(this.socketIoPort);
    this.ioServer = io;

    // listen to events of the socket.io server
    io.sockets.on('connection', (client) => {
      logger.debug(`[ClientSide]: client ${client.id} connected.`);

      // receive data
      client.on('dataToServer', (data) => {
        if (this.clientPacketHandler)
          this.clientPacketHandler(data, client.id);
        //logger.debug(`[ClientSide]: data from '${client.id}':\n>>>${JSON.stringify(data, null, 2)}<<<`);
      });

      // client disconnect
      client.on('disconnect', () => {
        this.clientDisconnectHandler(client.id);
      });
    });

    logger.info(`[ClientSide]: server runs at port ${this.socketIoPort}.`);
  }

  stop(callback) {
    this.ioServer.close(() => {
      this.ioServer = null;
      logger.info(`[ClientSide]: server is stop.`);
      callback();
    });
  }

  onData(handler) {
    this.clientPacketHandler = handler;
  }

  onDisconnect(handler) {
    this.clientDisconnectHandler = handler;
  }

  send(id, data) {
    this.ioServer.to(id).emit('dataToClient', data);
    logger.debug(`to client ${id}:\n${JSON.stringify(data)}`);
  }

  broadcast(data) {
    this.ioServer.emit('dataToClient', data);
  }
}

/*
 * Run Server
 */

logger = new Logger();
const gameServer = new GameServer();
