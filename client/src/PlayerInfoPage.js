import React from 'react';

class PlayerInfoPage extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      playerInfo: null
    };

    this.props.appUtils.serverSide.addListener('player-info', (packet) => {
      if (packet.type !== 'gameLogicEngineMessage')
        return;
      
      const data = packet.data;
      if (data.eventType === 'accountSystem') {
        // get player info
        if (data.function === 'getAccountInfo') {
          if (data.returnValue.success) {
            const userId = this.props.appUtils.getUserInfo().userId;
            const returnInfo = data.returnValue[userId];
            this.setState((state) => Object.assign(state, {playerInfo: {
              userId: userId,
              username: returnInfo.accountName,
              money: returnInfo.money,
              ladderPoint: returnInfo.ladderPoint,
              ladderLevel: returnInfo.ladderLevel,
              win: returnInfo.win,
              lose: returnInfo.lose,
              level: returnInfo.level,
              exp: returnInfo.exp
            }}));
          }
        } else if (data.function === 'payMoney') {
          this.sendPlayerInfoPacket();
        }
      }
    });
    this.sendPlayerInfoPacket = this.sendPlayerInfoPacket.bind(this);
    this.sendPlayerInfoPacket();
  }

  sendPlayerInfoPacket() {
    this.props.appUtils.serverSide.send({
      eventType: 'accountSystem',
      function: 'getAccountInfo',
      params: [
        this.props.appUtils.getUserInfo().userId
      ]
    });
    this.props.appUtils.setGoBackHandler(this.props.goBackPrevPage);
  }

  getMoney(money) {
    this.props.appUtils.serverSide.send({
      eventType: 'accountSystem',
      function: 'payMoney',
      params: [money]
    });
  }

  render() {
    const info = this.state.playerInfo;
    return (
      <div className="full-size">
        <div id="player-info-page">
          <div className="get-money-container">
            <button id="100" className="clickable" onClick={() => {this.getMoney(100);}}>氪金100元!!</button>
            <button id="500" className="clickable" onClick={() => {this.getMoney(500);}}>氪金500元!!</button>
            <button id="1000" className="clickable" onClick={() => {this.getMoney(1000);}}>氪金1000元!!</button>
          </div>
          <div className="info-container">
            <ul>
              <li key="username">帳號: {info && info.username}</li>
              <li key="userId">ID: {info && info.userId}</li>
              <li key="exp">經驗值: {info && info.exp}</li>
              <li key="money">額度: {info && info.money}</li>
              <li key="level">等級: {info && info.level}</li>
              <li key="win">勝局: {info && info.win}</li>
              <li key="lose">敗局: {info && info.lose}</li>
              <li key="ladderPoint">天梯積分: {info && info.ladderPoint}</li>
              <li key="ladderLevel">天梯等級: {info && info.ladderLevel}</li>
            </ul>
          </div>
        </div>
      </div>
    );
  }
}

export default PlayerInfoPage;
