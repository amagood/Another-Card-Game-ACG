class LoginForm extends React.Component {
  constructor(props) {
    super(props);
    this.state = {};
  }

  render() {
    return (
      <form id="login-form">
        <InputRow labelText="帳號" inputId="input-account" inputType="text"/>
        <InputRow labelText="密碼" inputId="input-password" inputType="password"/>
        <input type="submit" value="登入" />
      </form>
    );
  }
}
