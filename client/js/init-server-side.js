class ServerSide {
  constructor(options) {
    this.port = options.port;
    this._handlers = {};

    this.io = io(':' + this.port);
    this.io.on('sendData', (data) => {
      if (this._handlers.sendData) {
        this._handlers.sendData();
      }
    });
  }

  on(event, handler) {
    this._handlers[event] = handler;
  }

  send(data) {
    this.io.emit('sendData', data);
  }
}

function initServerSide() {
  window.serverSide = new ServerSide({
    port: 3456
  }); 
}