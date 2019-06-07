import * as serviceWorker from './serviceWorker';
import './index.scss';
import AcgAppController from './AcgAppController';

window.acgAppController = new AcgAppController();

// If you want your app to work offline and load faster, you can change
// unregister() to register() below. Note this comes with some pitfalls.
// Learn more about service workers: https://bit.ly/CRA-PWA
serviceWorker.unregister();
