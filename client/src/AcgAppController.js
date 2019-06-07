//import React from 'react';
import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';
import ServerSide from './ServerSide';
import util from './Util';

class AcgAppController {
  constructor() {
    // cofig logger
    window.logger = new util.Logger();

    // init server side communication
    this.serverSide = new ServerSide({port: 3456});
    this.serverSide.on('dataToClient', (data) => {
      window.logger.log(`from server:\n${JSON.stringify(data, 2)}`);
    });

    // config app size
    util.adjustWindowSize();
    window.addEventListener('orientationchange', util.adjustWindowSize);    
    window.addEventListener('resize', util.adjustWindowSize);

    // render app
    this.app = ReactDOM.render(
      <App serverSide={this.serverSide} />,
      document.getElementById('root')
    );
  }
}

export default AcgAppController;
