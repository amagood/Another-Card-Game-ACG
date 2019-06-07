const util = {};

util.Logger = class {
  constructor(options={}) {
    this.console = options.console || window.console;
    this.levelOrder = ['debug', 'info', 'warn', 'error'];
    this.level = this.levelOrder.indexOf(options.level);
    if (this.level < 0)
      this.level = this.levelOrder.length - 1;
  }

  log(message) {
    this.console.log(message);
  }

  debug(message) {
    if (this.level >= this.levelOrder.indexOf('debug'))
      this.console.debug(`[DEBUG] ${message}`);
  }

  info(message) {
    if (this.level >= this.levelOrder.indexOf('info'))
      this.console.info(`[INFO] ${message}`);
  }

  warn(message) {
    if (this.level >= this.levelOrder.indexOf('warn'))
      this.console.warn(`[WARN] ${message}`);
  }

  error(message) {
    if (this.level >= this.levelOrder.indexOf('error'))
      this.console.error(`[ERROR] ${message}`);
  }
};

util.calculateRem = (customWidth, customHeight) => {
  const width = customWidth || document.documentElement.clientWidth;
  const height = customHeight || document.documentElement.clientHeight;

  let rem;

  if (width * 9 < height * 16) // portrait
    rem = width / 32;
  else // landscape
    rem = height / 18;

  return rem;
};

util.adjustWindowSize = () => {
  document.documentElement.style.fontSize = `${util.calculateRem()}px`;
};

export default util;
