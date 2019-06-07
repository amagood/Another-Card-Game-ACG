import io from'socket.io-client';

class ServerSide {
  constructor(options) {
    this.port = options.port;
    this._handlers = {};
    this.userId = 0;

    this.io = io(':' + this.port);
    this.io.on('dataToClient', (data) => {
      if (this._handlers.dataToClient) {
        this._handlers.dataToClient(data);
      }
    });
  }

  on(event, handler) {
    this._handlers[event] = handler;
  }

  setUserId(id) {
    if (id <= 0)
      id = 0;
    this.userId = id;
  }

  send(data) {
    this.io.emit('dataToServer', {
      time: Date.now(),
      type: 'gameLogicEngineMessage',
      userId: this.id,
      data: data
    });
  }

  sendRawObject(data) {
    this.io.emit('dataToServer', data);
  }
}

export default ServerSide;
