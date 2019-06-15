import React from 'react';
import InputRow from './InputRow';

class ChatPage extends React.Component {
  constructor(props) {
    super(props);
    this.state = {};

    this.handleSendMessage = this.handleSendMessage.bind(this);
    this.props.appUtils.setGoBackHandler(this.props.goBackPrevPage);
  }

  handleSendMessage() {
    const sendTo = parseInt(document.getElementById('chat-send-to').value, 10) || 0;
    const message = document.getElementById('chat-message').value.toString().trim();
    document.getElementById('chat-message').value = '';
    this.props.appUtils.serverSide.sendRawObject({
      time: Date.now(),
      userId: this.props.appUtils.getUserInfo().userId,
      type: 'chat',
      data: {
        from: this.props.appUtils.getUserInfo().userId,
        to: sendTo,
        message: message
      }
    });
  }

  render() {
    return (
      <div id="chat-page">
        <div className="content-container">
          <InputRow labelText="傳送至(userId):" id="chat-send-to" type="text" />
          <InputRow labelText="訊息:" id="chat-message" type="text" />
          <button
            className="clickable"
            onClick={this.handleSendMessage}>
            傳送
          </button>
        </div>
      </div>
    );
  }
}

export default ChatPage;
