import io from'socket.io-client';

class ServerSide {
  constructor(options) {
    this.serverPort = options.port;
    this.listeners = {};
    this.userId = 0;

    this.io = io(':' + this.serverPort);

    // onData handler
    this.io.on('dataToClient', (data) => {
      window.logger.debug(`from server:\n${JSON.stringify(data, null, 2)}`);
      for (const identifier in this.listeners)
        this.listeners[identifier](data);
    });
  }

  addListener(identifier, handdler) {
    this.listeners[identifier] = handdler;
  }

  removeListener(identifier) {
    delete this.listeners[identifier];
  }

  setUserId(id) {
    if (id <= 0)
      id = 0;
    this.userId = id;
  }

  send(data) {
    this.sendRawObject({
      time: Date.now(),
      type: 'gameLogicEngineMessage',
      userId: this.userId,
      data: data
    });
  }

  sendRawObject(data) {
    this.io.emit('dataToServer', data);
  }
}

export default ServerSide;
