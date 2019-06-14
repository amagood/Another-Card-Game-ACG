class ConnectionManager {
  constructor(options) {
    this.logger = options.logger;
    this.clientSide = options.clientSide;
    this.serverSide = options.serverSide;
    this.userInfo = {};

    this.clientPacketHandlers = {
      // query login
      accountSystem: (packet, send, connectionId) => {
        if (packet.data.function === 'login') {
          packet.connectionId = connectionId;
          packet.data.params.push(connectionId);
          send(packet);
        } else if (packet.data.function === 'createAccount') {
          packet.connectionId = connectionId;
          packet.data.params.push(connectionId);
          send(packet);
        } else {
          send(packet);
        }
      },

      // pass packet to server directly
      default: (packet, send) => {
        send(packet);
      }
    };

    this.serverPacketHandlers = {
      // login success
      accountSystem: (packet, send) => {
        if (packet.data.function === 'login') {
          if (packet.data.returnValue.success) {
            packet.userId = packet.data.returnValue.userId;
            this.registerUser(packet.userId, packet.data.returnValue.connectionId);
          }
          this.logger.debug(`login:${packet.userId}:\n${JSON.stringify(packet, null, 2)}`);
          send(packet);
        } else if (packet.data.function === 'createAccount') {
          send(packet, packet.connectionId);
        } else if (packet.data.function === 'logout') {
          if (packet.data.returnValue.success) {
            send(packet);
            this.unregisterUser(packet.userId);
          }
        } else {
          //this.logger.debug(`login faild:${packet.userId}:\n${JSON.stringify(packet, null, 2)}`);
          send(packet);
        }
      },

      // pass packet to client directly
      default: (packet, send) => {
        this.logger.debug(`default server handler:${packet.userId}:\n${JSON.stringify(packet, null, 2)}`);
        send(packet);
      }
    };

    // register handlers
    this.clientPacketHandler = this.clientPacketHandler.bind(this);
    this.clientSide.onData(this.clientPacketHandler);
    this.clientDisconnectHandler = this.clientDisconnectHandler.bind(this);
    this.clientSide.onDisconnect(this.clientDisconnectHandler);
    this.serverPacketHandler = this.serverPacketHandler.bind(this);
    this.serverSide.onData(this.serverPacketHandler);
  }

  clientPacketHandler(packet, connectionId) {
    this.logger.debug(`clientHandler userId:${this.toUserId(connectionId)},${packet.userId}:\n${JSON.stringify(packet, null, 2)}`);
    
    // check illegally sending data as other user
    const userId = this.toUserId(connectionId);
    if (packet.userId !== userId)
      return;
      
    // update last active time
    this.activeUser(userId);

    // Game Logic Engine message
    if (packet.type === 'gameLogicEngineMessage') {
      const handler = this.clientPacketHandlers[packet.data.eventType] ||
                      this.clientPacketHandlers['default'];
      handler(packet, (newPacket) => {
        this.serverSide.send(newPacket);
      }, connectionId);

    // chat
    } else if (packet.type === 'chat') {
      this.chatHandler(packet);
    }
  }

  serverPacketHandler(packet) {
    this.logger.debug(`serverHandler event:${packet.data.eventType}:\n${JSON.stringify(packet, null, 2)}`);

    const handler = this.serverPacketHandlers[packet.data.eventType] || this.serverPacketHandlers['default'];
    handler(packet, (newPacket, connectionId=undefined) => {
      connectionId = connectionId || this.toConnectionId(newPacket.userId);
      this.logger.debug(`to client userId:${newPacket.userId} connectionId:${connectionId}\n${JSON.stringify(newPacket)}`);
      if (connectionId.length) {
        this.clientSide.send(connectionId, newPacket);
      }
    });
  }

  chatHandler(packet) {
    // check illegally sending data as other user
    if (packet.data.from !== packet.userId)
      return;
    
    // rewrite packet
    const sendPacket = {
      time: packet.time,
      type: 'chat',
      userId: packet.data.to,
      data: {
        from: packet.data.from,
        to: packet.data.to,
        message: packet.data.message
      }
    };
    
    this.clientSide.send(
      this.toConnectionId(packet.data.to),
      sendPacket
    );
  }

  clientDisconnectHandler(connectionId) {
    const userId = this.toUserId(connectionId);
    if (!userId)
      return;
    this.sendLogoutToServer(userId);
  }

  sendLogoutToServer(userId) {
    this.serverSide.send({
      time: Date.now(),
      type: 'gameLogicEngineMessage',
      userId: userId,
      data: {
        eventType: 'accountSystem',
        function: 'logout',
        params: [userId]
      }
    });
  }

  registerUser(userId, connectionId) {
    this.userInfo[userId] = {};
    this.userInfo[userId].connectionId = connectionId;
    this.activeUser(userId);
    //this.logger.dir(this.userInfo[userId]);
  }

  unregisterUser(userId) {
    delete this.userInfo[userId];
    this.logger.debug(`unregister user: ${userId}`);
  }

  activeUser(userId) {
    const info = this.userInfo[userId];

    // cannot find the user
    if (!info)
      return;

    // reset timer
    if (info.logoutTimeoutTimer !== undefined)
      clearTimeout(info.logoutTimeoutTimer);
    info.lastActiveTime = Date.now();
    info.logoutTimeoutTimer = setTimeout(() => {
      this.logger.debug(`user timeout: ${userId}`);
      this.sendLogoutToServer(userId);
    }, 1800 * 1000); // 30min
  }

  toUserId(connectionId) {
    // lookup userInfo to find
    for (const userId in this.userInfo) {
      if (this.userInfo[userId].connectionId === connectionId)
        return parseInt(userId, 10);
    }

    // cannot find user
    return 0;
  }

  toConnectionId(userId) {
    const info = this.userInfo[userId];
    if (info)
      return info.connectionId;
    
    // cannot find user
    return '';
  }
}

module.exports = ConnectionManager;
