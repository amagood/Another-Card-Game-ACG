import React from 'react';
import LoginPage from './LoginPage';
import GoBackButton from './GoBackButton';
import {DialogController} from './Dialog';
import ServerSide from './ServerSide';

class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {};
    this.promptDialog = null;
    this.setGoBackHandler = () => {};
    this.userInfo = {
      userId: 0,
      userName: ''
    };

    // init server side communication
    this.serverSide = new ServerSide({port: 3456});

    // bind methods
    this.getUserInfo = this.getUserInfo.bind(this);
    this.setUserInfo = this.setUserInfo.bind(this);
    this.playBgm = this.playBgm.bind(this);

    // make child-page params
    this.appUtils = {
      serverSide: this.serverSide,
      getUserInfo: this.getUserInfo,
      setUserInfo: this.setUserInfo,
      promptDialog: (...args) => this.promptDialog(...args),
      setGoBackHandler: (...args) => this.setGoBackHandler(...args),
      playBgm: this.playBgm
    };

    // config audio
    this.audio = {
      clickSound: new Audio('click-sound.wav'),
      bgmNormal: new Audio('bgm-normal.mp3'),
      bgmBattle: new Audio('bgm-battle.mp3')
    };

    for (const audioName in this.audio) {
      if (audioName.startsWith('bgm')) {
        this.audio[audioName].volume = 0.3;
        this.audio[audioName].loop = true;
      }
    }

    // config click sound
    const appElement = document.getElementById('app');
    window.addEventListener('click', (e) => {
      let target = e.target;
      while (target && target !== appElement) {
        if (target.classList.contains('clickable')) {
          this.audio.clickSound.currentTime = 0;
          this.audio.clickSound.play();
          break;
        }
        target = target.parentElement;
      }
    });
  }

  getUserInfo() {
    return this.userInfo;
  }

  setUserInfo(info) {
    if (typeof info === 'function')
      this.userInfo = info(this.getUserInfo);
    else
      this.userInfo = info;
    
    this.serverSide.setUserId(this.userInfo.userId);
  }

  playBgm(audioName) {
    for (const audio in this.audio) {
      this.audio[audio].pause();
      this.audio[audio].currentTime = 0;
      if (audio === audioName)
        this.audio[audioName].play();
    }
  }

  render() {
    return (
      <div id="app">
        <LoginPage appUtils={this.appUtils} />
        <GoBackButton returnSetGoBackHandlerFun={(fun) => {
          this.setGoBackHandler = fun;
        }} />
        <DialogController returnPromptDialogFun={(fun) => {
          this.promptDialog = fun;
        }} />
      </div>
    );
  }
}

export default App;
