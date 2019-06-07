import React from 'react';
import LoginPage from './LoginPage';

class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
    };
  }

  render() {
    return (
      <div id="app">
        {<LoginPage serverSide={this.props.serverSide} />}
      </div>
    );
  }
}

export default App;
