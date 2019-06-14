import React from 'react';

class GobackButton extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      goBackHandler: null
    };
    this.goBackHandler = this.goBackHandler.bind(this);
    this.setGoBackHandler = this.setGoBackHandler.bind(this);
    this.props.returnSetGoBackHandlerFun(this.setGoBackHandler);
  }

  setGoBackHandler(handler) {
    this.setState((state) => Object.assign(state, {
      goBackHandler: handler
    }));
  }

  goBackHandler() {
    if (this.state.goBackHandler) {
      this.state.goBackHandler();
    }
  }

  render() {
    return (
      <div id="go-back-button-container">
        <button
          className="clickable"
          onClick={this.goBackHandler}>
          ←
        </button>
      </div>
    );
  }
}

export default GobackButton;
