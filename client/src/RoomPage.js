import React from 'react';
import RoomWaitingPage from './RoomWaitingPage';
import InputRow from './InputRow';

class RoomPage extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      nextPage: null,
      roomMode: -1,
      roomList: {},
      creatingRoom: false,
    };
    this.nextRoomId = 0;

    this.props.appUtils.serverSide.addListener('room-page', (packet) => {
      if (packet.type !== 'gameLogicEngineMessage')
        return;

      if (!this.state.nextPage && packet.data.eventType === 'room') {
        const data = packet.data;

        // return room list
        if (data.action === 'getRoomList') {
          for (let i = 0; i < data.roomId.length; ++i) {
            this.setState((state) => {
              state = {...state};
              state.roomList[data.roomId[i]] = null;
              return state;
            });
            this.props.appUtils.serverSide.send({
              eventType: 'room',
              action: 'getRoomInfo',
              roomMode: data.roomMode,
              roomId: data.roomId[i]
            });
          }

        // return room info
        } else if (data.action === 'getRoomInfo') {
          this.setState((state) => {
            state = {...state};
            state.roomList[data.roomId] = {
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
        
        // return result of create room
        } else if (data.action === 'createRoom') {
          if (data.result) {
            this.nextRoomId = data.roomId;
            this.props.appUtils.promptDialog(
              'info',
              `成功建立並加入房間😏~\n房間編號: ${data.roomId}\n房間名稱: ${data.roomName}`,
              () => {
                this.setState((state) => Object.assign(state, {
                  nextPage: 'room-waiting-page',
                }));
              }
            );
            
          } else {
            this.props.appUtils.promptDialog('error', '建立房間失敗😰');
          }

        // enter room
        } else if (data.action === 'enterRoom' || data.action === 'enterRoomRandom') {
          if (data.result) {
            this.nextRoomId = data.roomId;
            this.setState((state) => Object.assign(state, {
              nextPage: 'room-waiting-page'
            }));
          } else {
            this.props.appUtils.promptDialog('error', '⛔無法加入房間⛔\n別問我為啥因為我也不知道🙄!');
          }
        }
      }
    });

    this.handleClickCreateRoomButton = this.handleClickCreateRoomButton.bind(this);
    this.goBackThisPage = this.goBackThisPage.bind(this);
    this.props.appUtils.setGoBackHandler(this.props.goBackPrevPage);
  }

  goBackThisPage() {
    this.setState((state) => Object.assign(state, {
      nextPage: null
    }));
    this.props.appUtils.setGoBackHandler(this.props.goBackPrevPage);
  }

  setRoomMode(roomMode) {
    this.setState((state) => Object.assign(state, {
      roomMode: roomMode,
      roomList: {},
      creatingRoom: false
    }));
    this.getRoomList(roomMode);
  }

  getRoomList(roomMode) {
    this.props.appUtils.serverSide.send({
      eventType: 'room',
      action: 'getRoomList',
      roomMode: roomMode
    });
  }

  handleClickCreateRoomButton() {
    this.setState((state) => Object.assign(state, {
      creatingRoom: true
    }));
  }

  createRoom(roomName) {
    this.props.appUtils.serverSide.send({
      eventType: 'room',
      action: 'createRoom',
      roomMode: this.state.roomMode,
      roomName: roomName,
      roomPassword: '',
      userId: this.props.appUtils.getUserInfo().userId
    });
  }

  handleEnterRoomButton(roomId) {
    this.props.appUtils.serverSide.send({
      eventType: 'room',
      action: roomId === -1 ? 'enterRoomRandom' : 'enterRoom',
      roomMode: this.state.roomMode,
      roomId: roomId === -1 ? undefined : roomId,
      roomPassword: '',
      userId: this.props.appUtils.getUserInfo().userId
    });
  }

  renderCreateRoomForm() {
    return (
      <div id="create-room-form">
        <InputRow labelText="房間名稱" id="create-room-name" type="text" />
        <button
          className="clickable"
          onClick={() => {
            this.createRoom(
              document.getElementById('create-room-name').value
            );
            this.setState((state) => Object.assign(state, {
              creatingRoom: false
            }));
          }}>
          建立
        </button>
      </div>
    );
  }

  renderRoomList() {
    const roomList = [];

    // create room button
    const buttons = [];

    if (this.state.roomMode >= 0) {
      buttons.push(
        <button
          key="enter-room-random"
          onClick={() => {this.handleEnterRoomButton(-1);}}
          className="clickable">
          隨機進房
        </button>
      );
    }

    if (this.state.roomMode === 1) {
      buttons.push(
        <button
          key="create-room"
          onClick={this.handleClickCreateRoomButton}
          className="clickable">
          建立房間
        </button>
      );
    }

    roomList.push(<li key={-1}>{buttons}</li>);

    // append all rooms
    for (let roomId in this.state.roomList) {
      roomId = parseInt(roomId, 10);
      const room = this.state.roomList[roomId];
      const liContent = [];
      liContent.push(<span key="room-id" className="room-id">{roomId}</span>);

      if (room) {
        liContent.push(<span key="room-name" className="room-name">{room.roomName}</span>);
        liContent.push(<span key="room-level" className="room-level">{room.roomLevel}</span>);
        liContent.push(<span key="room-players" className="room-player">{room.playerId.length}人</span>);
      }

      roomList.push(
        <li
          key={roomId}
          onClick={() => {this.handleEnterRoomButton(roomId);}}
          className="clickable">{liContent}
        </li>
      );
    }

    return (<ul className="room-list">{roomList}</ul>);
  }

  render() {
    let windowContent;
    if (this.state.creatingRoom) {
      windowContent = this.renderCreateRoomForm();
    } else {
      windowContent = this.renderRoomList();
    }

    let nextPage;
    let thisPageStyle = 'hide';
    if (this.state.nextPage === 'room-waiting-page') {
      nextPage = (
        <RoomWaitingPage
          appUtils={this.props.appUtils}
          goBackPrevPage={this.goBackThisPage}
          roomId={this.nextRoomId}
        />
      );
    } else {
      thisPageStyle = undefined;
    }

    return (
      <div className="full-size">
        <div id="room-page" className={thisPageStyle}>
          <div id="room-page-select-mode">
            <button id="room-page-normal-mode-button" className="clickable" onClick={() => {this.setRoomMode(1);}}>一般模式</button>
            <button id="room-page-ladder-mode-button" className="clickable" onClick={() => {this.setRoomMode(2);}}>天梯模式</button>
          </div>
          <div className="content-window">
            {windowContent}
          </div>
        </div>
        {nextPage}
      </div>
    );
  }
}

export default RoomPage;
