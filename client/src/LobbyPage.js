import React from 'react';
import RoomPage from './RoomPage';
import CardPoolPage from './CardPoolPage';
import ModifyCardsPage from './ModifyCardsPage';
import PlayerInfoPage from './PlayerInfoPage';

class LobbyPage extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      nextPage: null,
    };

    this.goBackThisPage = this.goBackThisPage.bind(this);
    this.props.appUtils.setGoBackHandler(this.props.goBackPrevPage);

    // play bgm
    this.props.appUtils.playBgm('bgmNormal');
  }

  goBackThisPage() {
    this.setState((state) => Object.assign(state, {
      nextPage: null
    }));
    this.props.appUtils.setGoBackHandler(this.props.goBackPrevPage);
  }

  render() {
    let nextPage;
    let thisPageStyle = 'hide';
    if (this.state.nextPage === 'room') {
      nextPage = <RoomPage appUtils={this.props.appUtils} goBackPrevPage={this.goBackThisPage} />;
    } else if (this.state.nextPage === 'card-pool') {
      nextPage = <CardPoolPage appUtils={this.props.appUtils} goBackPrevPage={this.goBackThisPage} />;
    } else if (this.state.nextPage === 'modify-cards') {
      nextPage = <ModifyCardsPage appUtils={this.props.appUtils} goBackPrevPage={this.goBackThisPage}  />;
    } else if (this.state.nextPage === 'player-info') {
      nextPage = <PlayerInfoPage appUtils={this.props.appUtils} goBackPrevPage={this.goBackThisPage}  />;
    } else {
      thisPageStyle = undefined;
    }

    return (
      <div className="full-size">
        <div id="lobby-page" className={thisPageStyle}>
          <div className="button-container">
            <button key={1} className="clickable" onClick={() => {this.setState((state) => Object.assign(state, {nextPage: 'room'}));}}>選擇對戰模式</button>
            <button key={2} className="clickable" onClick={() => {this.setState((state) => Object.assign(state, {nextPage: 'card-pool'}));}}>卡池</button>
            <button key={3} className="clickable" onClick={() => {this.setState((state) => Object.assign(state, {nextPage: 'modify-cards'}));}}>修改排組</button>
            <button key={4} className="clickable" onClick={() => {this.setState((state) => Object.assign(state, {nextPage: 'player-info'}));}}>玩家資訊</button>
          </div>
        </div>
        {nextPage}
      </div>
    );
  }
}

export default LobbyPage;
