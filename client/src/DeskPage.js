import React from 'react';

class DeskPage extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      message: []
    };

    this.props.appUtils.serverSide.addListener('desk', (packet) => {
      const message = JSON.stringify(packet, null, 2);
      this.setState((state) => Object.assign(state, {
        message: [...state.message, message]
      }));
    });

    this.sendData = this.sendData.bind(this);
  }

  sendData() {
    const message = JSON.parse(document.getElementById('desk-input-textarea').value.trim());
    window.logger.debug(`senf from desk\n${JSON.stringify(message, null, 2)}`);
    this.props.appUtils.serverSide.send(message);
  }

  render() {
    const message = this.state.message;
    const messageNode = [];
    for (let i = 0; i < message.length; ++i) {
      messageNode.push(
        <p key={i}>{message}<br /></p>
      );
      messageNode.push(
        <hr key={'hr' + i} />
      );
    }

    return (
      <div id="desk-page">
        <div className="input-container">
          <textarea id="desk-input-textarea"></textarea>
          <button className="clickable" onClick={this.sendData}>傳送</button>
        </div>
        <div className="output-window" id="desk-output-window">{messageNode}</div>
      </div>
    );
  }
}

export default DeskPage;
