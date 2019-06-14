import React from 'react';
import DeskPage from './DeskPage';

class RoomWaitingPage extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      nextPage: null,
      roomInfo: null
    };

    this.props.appUtils.serverSide.addListener('room-waiting', (packet) => {
      if (packet.type !== 'gameLogicEngineMessage')
        return;

      const data = packet.data;
      if (data.eventType === 'room') {
        if (data.action === 'getRoomInfo') {
          this.setState((state) => {
            state = {...state};
            state.roomInfo = {
              roomMode: data.roomMode,
              roomId: data.roomId,
              roomName: data.roomName,
              roomLevel: data.roomLevel,
              playerId: data.playerId,
              full: data.full,
              playing: data.playing
            };
            return state;
          });
        }
      }
    });

    this.startGame = this.startGame.bind(this);
    this.goBackThisPage = this.goBackThisPage.bind(this);
    this.props.appUtils.setGoBackHandler(null);
  }

  goBackThisPage() {
    this.setState((state) => Object.assign(state, {
      nextPage: null
    }));
    this.props.appUtils.setGoBackHandler(this.props.goBackPrevPage);
  }

  startGame() {
    this.setState((state) => Object.assign(state, {
      nextPage: 'desk-page'
    }));
  }

  render() {
    const playerList = [];

    let nextPage;
    let thisPageStyle = 'hide';
    if (this.state.nextPage === 'desk-page') {
      nextPage = (
        <DeskPage
          appUtils={this.props.appUtils}
          goBackPrevPage={this.goBackThisPage}
          roomId={this.props.roomId}
        />
      );
    } else {
      thisPageStyle = undefined;
    }

    return (
      <div className="full-sized">
        <div id="room-waiting-page" className={thisPageStyle}>
          <div className="button-container">
            <button key="start" className="clickable" onClick={this.startGame}>
              <span role="img" aria-label="game">🎮</span>開始遊戲: {this.props.roomId}
            </button>
          </div>
          <div className="player-list">
            {playerList}
          </div>
        </div>
        {nextPage}
      </div>
    );
  }
}

export default RoomWaitingPage;
