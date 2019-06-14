//import React from 'react';
import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';
import util from './Util';

class AcgAppController {
  constructor() {
    // cofig logger
    window.logger = new util.Logger();

    // config app size
    util.adjustWindowSize();
    window.addEventListener('orientationchange', util.adjustWindowSize);    
    window.addEventListener('resize', util.adjustWindowSize);

    // render app
    this.app = ReactDOM.render(
      <App />,
      document.getElementById('root')
    );
  }
}

export default AcgAppController;
