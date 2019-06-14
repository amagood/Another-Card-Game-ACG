import React from 'react';

class CardPoolPage extends React.Component {
  constructor(props) {
    super(props);
    this.state = {};

    this.props.appUtils.serverSide.addListener('card-pool', (packet) => {
      if (packet.type !== 'gameLogicEngineMessage')
        return;

      const data = packet.data;
      if (data.eventType === 'accountSystem' && data.function === 'drawCards') {
        if (data.returnValue.success) {
          this.props.appUtils.promptDialog(
            'info',
            `抽卡成功😏~\n抽卡張數:${data.returnValue.amount}\n剩餘額度:${data.returnValue.money}`
          );
        } else {
          this.props.appUtils.promptDialog(
            'error',
            `抽卡失敗😰`
          );
        }
      }
    });

    this.drawCards = this.drawCards.bind(this);
    this.props.appUtils.setGoBackHandler(this.props.goBackPrevPage);
  }

  drawCards(num) {
    this.props.appUtils.serverSide.send({
      eventType: 'accountSystem',
      function: 'drawCards',
      params: [num]
    });
  }

  render() {
    return (
      <div id="card-pool-page">
        <div className="button-container">
          <button key={100} className="clickable" onClick={() => {this.drawCards(100);}}>
            <span role="img" aria-label="green-checked">✅一時抽卡一時爽✅<br />1張100</span>
          </button>
          <button key={1000} className="clickable" onClick={() => {this.drawCards(1000);}}>
            <span role="img" aria-label="heart">🧡一直抽卡一直爽🧡<br />11張1000</span>
          </button>
        </div>
      </div>
    );
  }
}

export default CardPoolPage;
