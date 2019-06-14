import React from 'react';
import InputRow from './InputRow';
import LobbyPage from './LobbyPage';

class LoginPage extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      nextPage: null
    };

    this.serverSide = this.props.appUtils.serverSide;
    this.handleSubmit = this.handleSubmit.bind(this);
    this.handleRegister = this.handleRegister.bind(this);
    this.goBackThisPage = this.goBackThisPage.bind(this);

    // listen to serverSide
    this.serverSide.addListener('login-page', (packet) => {
      if (!this.state.nextPage && packet.type !== 'gameLogicEngineMessage')
        return;
      const data = packet.data;

      // result of create acount
      if (data.eventType === 'accountSystem' && data.function === 'createAccount') {
        const message = `建立帳號${data.returnValue.success ? '成功! 🎉🎉🎉' : '失敗!\n可能的原因: 不合法的帳號或密碼或是已經有此使用者'}`;
        this.props.appUtils.promptDialog(
          data.returnValue.success ? 'info' : 'error',
          message
        );
      
      // result of login
      } else if (data.eventType === 'accountSystem' && data.function === 'login') {
        // login success
        if (data.returnValue.success) {
          document.getElementById('input-password').value = ''; // clear password
          // set userId
          this.props.appUtils.setUserInfo({
            userId: data.returnValue.userId
          });
          // goto lobby page
          this.setState((state) => {
            return Object.assign({}, state, {nextPage: 'lobby'});
          });
        }
      }
    });

    this.props.appUtils.setGoBackHandler(null);
  }

  handleSubmit(data) {
    this.serverSide.send({
      eventType: 'accountSystem',
      function: 'login',
      params: [data.username, data.password]
    });
  }

  handleRegister(data) {
    this.serverSide.send({
      eventType: 'accountSystem',
      function: 'createAccount',
      params: [data.username, data.password]
    });
  }

  goBackThisPage() {
    window.location.reload();
    /*this.setState((state) => Object.assign(state, {
      nextPage: null
    }));
    this.props.appUtils.setGoBackHandler(null);*/
  }

  render() {
    let thisPageStyle;
    let nextPage = 'hide';
    
    if (this.state.nextPage === 'lobby') {
      nextPage = (
        <LobbyPage appUtils={this.props.appUtils} goBackPrevPage={this.goBackThisPage} />
      );
    } else {
      thisPageStyle = undefined;
    }

    return (
      <div className="full-size">
        <div id="login-page" className={thisPageStyle}>
          <h1>
            <span>Another</span>
            <span>Card</span>
            <span>Game</span>
          </h1>
          <LoginForm
            onSubmit={this.handleSubmit}
            onRegister={this.handleRegister}
            promptDialog={this.props.appUtils.promptDialog}
          />
        </div>
        {nextPage}
      </div>
    );
  }
}

class LoginForm extends React.Component {
  constructor(props) {
    super(props);
    this.handleSubmit = this.handleSubmit.bind(this);
    this.handleRegister = this.handleRegister.bind(this);
  }

  handleSubmit(e) {
    e.preventDefault();
    this.props.onSubmit({
      username: document.getElementById('input-account').value,
      password: document.getElementById('input-password').value
    });
  }

  handleRegister(e) {
    e.preventDefault();
    const username = document.getElementById('input-account').value;
    const password = document.getElementById('input-password').value;

    const terms =
      '請先閱讀並同意以下使用條款:\n' +
      '本遊戲不會擅自在您未授權的情況下，將您的個人資料經由散佈、拍賣等方式移交給第三者，因為我們懶得做🙄。';
    const signUpInfo =
      `帳號: ${username}\n` +
      `密碼: ${'*'.repeat(password.length)}`;

    this.props.promptDialog('info', terms, () => {
      this.props.promptDialog('info', `確定齁🤔🤔?\n${signUpInfo}`, () => {
        this.props.onRegister({
          username: username,
          password: password
        });
      });
    });
  }

  render() {
    return (
      <form id="login-form">
        <InputRow labelText="帳號" id="input-account" type="text" autoComplete="username" />
        <InputRow labelText="密碼" id="input-password" type="password" autoComplete="current-password" />
        <input type="submit" value="登入" onClick={this.handleSubmit} className="clickable" />
        <button onClick={this.handleRegister} className="clickable">註冊</button>
      </form>
    );
  }
}

export default LoginPage;
