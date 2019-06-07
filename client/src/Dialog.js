import React from 'react';

class Dialog extends React.Component {
  render() {
    const title = {
      'info': '資訊',
      'warning': '警告',
      'error': '錯誤',
    }[this.props.type];

    return (
      <div className="dialog-container">
        <div className="dialog">
          <span className="dialog-title">{title}</span>
          <hr />
          <p>{this.props.message}</p>
          <span className="button-container">
            <button onClick={this.props.onOk}>確認</button>
          </span>
        </div>
      </div>
    );
  }
}

class DialogController extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      //dialogs
    };
    this.lastDialogIndex = 0;
  }
  
  promptDialog(type, message) {
    //const state = this.state;
    //state
  }

  generateIndex() {
    return ++this.lastDialogIndex;
  }
}

export default Dialog;
export {DialogController};
