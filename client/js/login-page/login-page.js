class LoginPage extends React.Component {
  constructor(props) {
    super(props);
    this.state = {};
  }

  render() {
    return (
      <div id="login-page" className="full-filled">
        <h1>
          <span>Another</span>
          <span>Card</span>
          <span>Game</span>
        </h1>
        <LoginForm />
      </div>
    );
  }
}
