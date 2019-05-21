function calculateRem(customWidth, customHeight) {
  const width = customWidth || document.documentElement.clientWidth;
  const height = customHeight || document.documentElement.clientHeight;

  let rem;

  if (width * 9 < height * 16) // portal
    rem = width / 32;
  else // landscape
    rem = height / 18;

  document.documentElement.style.fontSize = `${rem}px`;

  return rem;
}

function handleWindowResize(event) {
  let rem = calculateRem();
  console.log('resize to (' + document.documentElement.clientWidth + ', ' 
      + document.documentElement.clientHeight + ') rem: ' + rem + 'px.');
}

function init() {
  calculateRem();

  window.addEventListener('resize', handleWindowResize);
  window.addEventListener('orientationchange', handleWindowResize);

  initServerSide();

  initReact();
}

// init
init();
