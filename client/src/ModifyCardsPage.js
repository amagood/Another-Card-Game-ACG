import React from 'react';

class ModifyCardsPage extends React.Component {
  constructor(props) {
    super(props);
    this.state = {};

    this.props.appUtils.serverSide.addListener('modify-cards', (packet) => {
      if (packet.type !== 'gameLogicEngineMessage')
        return;

      const data = packet.data;
      if (data.eventType === 'accountSystem') {
        if ((data.function === 'getCards' || data.function === 'modifyCards') /*&& data.returnValue.success*/) {
          this.setState((state) => Object.assign(state, {
            deck: [...data.returnValue.deck].sort((a, b) => a - b),
            amounts: data.returnValue.amounts,
            cards: [...data.returnValue.cards].sort((a, b) => a - b)
          }));
        }
      }
    });

    this.getCards = this.getCards.bind(this);
    this.modifyCards = this.modifyCards.bind(this);
    this.props.appUtils.setGoBackHandler(this.props.goBackPrevPage);

    this.getCards();
  }

  getCards() {
    this.props.appUtils.serverSide.send({
      eventType: 'accountSystem',
      function: 'getCards',
      params: [this.props.appUtils.getUserInfo().userId]
    });
  }

  modifyCards() {
    const newCards = [...this.state.cards];
    for (let i = 0; i < newCards.length; ++i) {
      const randomIndex = Math.floor(Math.random() * newCards.length);
      [newCards[i], newCards[randomIndex]] = [newCards[randomIndex], newCards[i]];
    }

    this.props.appUtils.serverSide.send({
      eventType: 'accountSystem',
      function: 'modifyCards',
      params: [this.props.appUtils.getUserInfo().userId],
      deck: newCards.splice(0, 30)
    });
  }

  render() {
    const content = [
      <p key="deck">
        牌組: {this.state.deck && this.state.deck.join(', ')}
      </p>,
      <p key="amount">
        卡片總數: {this.state.amounts || ''}
      </p>,
      <p key="cards">
        所有卡牌: {this.state.cards && this.state.cards.join(', ')}
      </p>
    ];

    return (
      <div className="full-size">
        <div id="modify-cards-page">
          <div className="content-container">
            <div key="cards-info" className="cards-info">{content}</div>
            <div key="button-container" className="button-container">
              <button className="clickable" onClick={this.modifyCards}>
                <span role="img" aria-label="dice">🎲</span>隨機組牌
              </button>
            </div>
          </div>
        </div>
      </div>
    );
  }
}

export default ModifyCardsPage;
