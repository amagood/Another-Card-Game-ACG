import React from 'react';

class Dialog extends React.Component {
  render() {
    const title = {
      'info': '訊息',
      'warning': '警告',
      'error': '錯誤',
    }[this.props.type];

    return (
      <div className="dialog-container">
        <div className="dialog">
          <span className="dialog-title">{title}</span>
          <hr />
          <div className="dialog-message">{this.props.message}</div>
          <span className="button-container">
            <button onClick={this.props.onOk} className="clickable">確認</button>
          </span>
        </div>
      </div>
    );
  }
}

class DialogController extends React.Component {
  constructor(props) {
    super(props);
    this.state = {};
    this.state.dialogs = [];
    this.lastDialogIndex = 0;

    this.promptDialog = this.promptDialog.bind(this);
    // return promptDialog method to parent
    if (props.returnPromptDialogFun)
      props.returnPromptDialogFun(this.promptDialog);
  }

  promptDialog(type, message, callback=null) {
    this.setState((state) => {
      state = {...state};
      state.dialogs.push({
        dialogId: ++this.lastDialogIndex,
        type: type,
        message: message,
        callback: callback
      });
      return state;
    });
  }

  handleClearDialog(dialogId) {
    this.setState((state) => {
      for(let i = 0; i < state.dialogs.length; ++i) {
        if (state.dialogs[i].dialogId === dialogId) {
          state.dialogs.splice(i, 1);
        }
      }
      return state;
    });
  }

  render() {
    const dialogElements = [];
    for (let i = 0; i < this.state.dialogs.length; ++i) {
      const dialog = this.state.dialogs[i];
      dialogElements.push(
        <Dialog
          key={dialog.dialogId}
          type={dialog.type}
          message={dialog.message}
          onOk={() => {
            this.handleClearDialog(dialog.dialogId);
            if (dialog.callback)
              dialog.callback();
          }}
        />
      );
    }

    return (
      <div id="dialog-container">
        {dialogElements}
      </div>
    );
  }
}

export default Dialog;
export {DialogController};
