import React from 'react';
import InputRow from './InputRow';
import Dialog from './Dialog';

class LoginPage extends React.Component {
  constructor(props) {
    super(props);
    this.serverSide = this.props.serverSide;
    this.handleSubmit = this.handleSubmit.bind(this);
    this.handleRegister = this.handleRegister.bind(this);
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

  render() {
    return (
      <div id="login-page" className="full-filled">
        <h1>
          <span>Another</span>
          <span>Card</span>
          <span>Game</span>
        </h1>
        <LoginForm onSubmit={this.handleSubmit} onRegister={this.handleRegister} />
        <Dialog type="warning" message="不要一直亂登入啦~" />
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
    window.console.log();
    this.props.onSubmit({
      username: document.getElementById('input-account').value,
      password: document.getElementById('input-password').value
    });
  }

  handleRegister(e) {
    e.preventDefault();
    this.props.onRegister({
      username: document.getElementById('input-account').value,
      password: document.getElementById('input-password').value
    });
  }

  render() {
    return (
      <form id="login-form">
        <InputRow labelText="帳號" id="input-account" type="text" autoComplete="username" />
        <InputRow labelText="密碼" id="input-password" type="password" autoComplete="current-password" />
        <input type="submit" value="登入" onClick={this.handleSubmit} />
        <button onClick={this.handleRegister}>註冊</button>
      </form>
    );
  }
}

export default LoginPage;
