(window.webpackJsonp=window.webpackJsonp||[]).push([[0],{37:function(e,t,a){e.exports=a(72)},38:function(e,t,a){},69:function(e,t){},72:function(e,t,a){"use strict";a.r(t);Boolean("localhost"===window.location.hostname||"[::1]"===window.location.hostname||window.location.hostname.match(/^127(?:\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}$/));a(38);var n=a(2),o=a(0),r=a.n(o),s=a(35),i=a.n(s),c=a(3),l=a(5),u=a(4),d=a(1),p=a(6),m=function(e){function t(){return Object(n.a)(this,t),Object(l.a)(this,Object(u.a)(t).apply(this,arguments))}return Object(p.a)(t,e),Object(c.a)(t,[{key:"render",value:function(){return r.a.createElement("div",{className:"input-row"},r.a.createElement("label",{htmlFor:this.props.id},this.props.labelText),r.a.createElement("input",{type:this.props.type,id:this.props.id,autoComplete:this.props.autoComplete,onChange:this.props.onChange}))}}]),t}(r.a.Component),g=a(7),h=a(9),f=function(e){function t(e){var a;return Object(n.a)(this,t),(a=Object(l.a)(this,Object(u.a)(t).call(this,e))).state={message:[]},a.props.appUtils.serverSide.addListener("desk",function(e){var t=JSON.stringify(e,null,2);a.setState(function(e){return Object.assign(e,{message:[].concat(Object(h.a)(e.message),[t])})})}),a.sendData=a.sendData.bind(Object(d.a)(a)),a}return Object(p.a)(t,e),Object(c.a)(t,[{key:"sendData",value:function(){var e=JSON.parse(document.getElementById("desk-input-textarea").value.trim());window.logger.debug("senf from desk\n".concat(JSON.stringify(e,null,2))),this.props.appUtils.serverSide.send(e)}},{key:"render",value:function(){for(var e=this.state.message,t=[],a=0;a<e.length;++a)t.push(r.a.createElement("p",{key:a},e,r.a.createElement("br",null))),t.push(r.a.createElement("hr",{key:"hr"+a}));return r.a.createElement("div",{id:"desk-page"},r.a.createElement("div",{className:"input-container"},r.a.createElement("textarea",{id:"desk-input-textarea"}),r.a.createElement("button",{className:"clickable",onClick:this.sendData},"\u50b3\u9001")),r.a.createElement("div",{className:"output-window",id:"desk-output-window"},t))}}]),t}(r.a.Component),v=function(e){function t(e){var a;return Object(n.a)(this,t),(a=Object(l.a)(this,Object(u.a)(t).call(this,e))).state={nextPage:null,roomInfo:null},a.props.appUtils.serverSide.addListener("room-waiting",function(e){if("gameLogicEngineMessage"===e.type){var t=e.data;"room"===t.eventType&&"getRoomInfo"===t.action&&a.setState(function(e){return(e=Object(g.a)({},e)).roomInfo={roomMode:t.roomMode,roomId:t.roomId,roomName:t.roomName,roomLevel:t.roomLevel,playerId:t.playerId,full:t.full,playing:t.playing},e})}}),a.startGame=a.startGame.bind(Object(d.a)(a)),a.goBackThisPage=a.goBackThisPage.bind(Object(d.a)(a)),a.props.appUtils.setGoBackHandler(null),a}return Object(p.a)(t,e),Object(c.a)(t,[{key:"goBackThisPage",value:function(){this.setState(function(e){return Object.assign(e,{nextPage:null})}),this.props.appUtils.setGoBackHandler(this.props.goBackPrevPage)}},{key:"startGame",value:function(){this.setState(function(e){return Object.assign(e,{nextPage:"desk-page"})})}},{key:"render",value:function(){var e,t="hide";return"desk-page"===this.state.nextPage?e=r.a.createElement(f,{appUtils:this.props.appUtils,goBackPrevPage:this.goBackThisPage,roomId:this.props.roomId}):t=void 0,r.a.createElement("div",{className:"full-sized"},r.a.createElement("div",{id:"room-waiting-page",className:t},r.a.createElement("div",{className:"button-container"},r.a.createElement("button",{key:"start",className:"clickable",onClick:this.startGame},r.a.createElement("span",{role:"img","aria-label":"game"},"\ud83c\udfae"),"\u958b\u59cb\u904a\u6232: ",this.props.roomId)),r.a.createElement("div",{className:"player-list"},[])),e)}}]),t}(r.a.Component),b=function(e){function t(e){var a;return Object(n.a)(this,t),(a=Object(l.a)(this,Object(u.a)(t).call(this,e))).state={nextPage:null,roomMode:-1,roomList:{},creatingRoom:!1},a.nextRoomId=0,a.props.appUtils.serverSide.addListener("room-page",function(e){"gameLogicEngineMessage"===e.type&&(a.state.nextPage||"room"!==e.data.eventType||function(){var t=e.data;if("getRoomList"===t.action)for(var n=function(e){a.setState(function(a){return(a=Object(g.a)({},a)).roomList[t.roomId[e]]=null,a}),a.props.appUtils.serverSide.send({eventType:"room",action:"getRoomInfo",roomMode:t.roomMode,roomId:t.roomId[e]})},o=0;o<t.roomId.length;++o)n(o);else"getRoomInfo"===t.action?a.setState(function(e){return(e=Object(g.a)({},e)).roomList[t.roomId]={roomMode:t.roomMode,roomId:t.roomId,roomName:t.roomName,roomLevel:t.roomLevel,playerId:t.playerId,full:t.full,playing:t.playing},e}):"createRoom"===t.action?t.result?(a.nextRoomId=t.roomId,a.props.appUtils.promptDialog("info","\u6210\u529f\u5efa\u7acb\u4e26\u52a0\u5165\u623f\u9593\ud83d\ude0f~\n\u623f\u9593\u7de8\u865f: ".concat(t.roomId,"\n\u623f\u9593\u540d\u7a31: ").concat(t.roomName),function(){a.setState(function(e){return Object.assign(e,{nextPage:"room-waiting-page"})})})):a.props.appUtils.promptDialog("error","\u5efa\u7acb\u623f\u9593\u5931\u6557\ud83d\ude30"):"enterRoom"!==t.action&&"enterRoomRandom"!==t.action||(t.result?(a.nextRoomId=t.roomId,a.setState(function(e){return Object.assign(e,{nextPage:"room-waiting-page"})})):a.props.appUtils.promptDialog("error","\u26d4\u7121\u6cd5\u52a0\u5165\u623f\u9593\u26d4\n\u5225\u554f\u6211\u70ba\u5565\u56e0\u70ba\u6211\u4e5f\u4e0d\u77e5\u9053\ud83d\ude44!"))}())}),a.handleClickCreateRoomButton=a.handleClickCreateRoomButton.bind(Object(d.a)(a)),a.goBackThisPage=a.goBackThisPage.bind(Object(d.a)(a)),a.props.appUtils.setGoBackHandler(a.props.goBackPrevPage),a}return Object(p.a)(t,e),Object(c.a)(t,[{key:"goBackThisPage",value:function(){this.setState(function(e){return Object.assign(e,{nextPage:null})}),this.props.appUtils.setGoBackHandler(this.props.goBackPrevPage)}},{key:"setRoomMode",value:function(e){this.setState(function(t){return Object.assign(t,{roomMode:e,roomList:{},creatingRoom:!1})}),this.getRoomList(e)}},{key:"getRoomList",value:function(e){this.props.appUtils.serverSide.send({eventType:"room",action:"getRoomList",roomMode:e})}},{key:"handleClickCreateRoomButton",value:function(){this.setState(function(e){return Object.assign(e,{creatingRoom:!0})})}},{key:"createRoom",value:function(e){this.props.appUtils.serverSide.send({eventType:"room",action:"createRoom",roomMode:this.state.roomMode,roomName:e,roomPassword:"",userId:this.props.appUtils.getUserInfo().userId})}},{key:"handleEnterRoomButton",value:function(e){this.props.appUtils.serverSide.send({eventType:"room",action:-1===e?"enterRoomRandom":"enterRoom",roomMode:this.state.roomMode,roomId:-1===e?void 0:e,roomPassword:"",userId:this.props.appUtils.getUserInfo().userId})}},{key:"renderCreateRoomForm",value:function(){var e=this;return r.a.createElement("div",{id:"create-room-form"},r.a.createElement(m,{labelText:"\u623f\u9593\u540d\u7a31",id:"create-room-name",type:"text"}),r.a.createElement("button",{className:"clickable",onClick:function(){e.createRoom(document.getElementById("create-room-name").value),e.setState(function(e){return Object.assign(e,{creatingRoom:!1})})}},"\u5efa\u7acb"))}},{key:"renderRoomList",value:function(){var e=this,t=[],a=[];this.state.roomMode>=0&&a.push(r.a.createElement("button",{key:"enter-room-random",onClick:function(){e.handleEnterRoomButton(-1)},className:"clickable"},"\u96a8\u6a5f\u9032\u623f")),1===this.state.roomMode&&a.push(r.a.createElement("button",{key:"create-room",onClick:this.handleClickCreateRoomButton,className:"clickable"},"\u5efa\u7acb\u623f\u9593")),t.push(r.a.createElement("li",{key:-1},a));var n=function(a){a=parseInt(a,10);var n=e.state.roomList[a],s=[];s.push(r.a.createElement("span",{key:"room-id",className:"room-id"},a)),n&&(s.push(r.a.createElement("span",{key:"room-name",className:"room-name"},n.roomName)),s.push(r.a.createElement("span",{key:"room-level",className:"room-level"},n.roomLevel)),s.push(r.a.createElement("span",{key:"room-players",className:"room-player"},n.playerId.length,"\u4eba"))),t.push(r.a.createElement("li",{key:a,onClick:function(){e.handleEnterRoomButton(a)},className:"clickable"},s)),o=a};for(var o in this.state.roomList)n(o);return r.a.createElement("ul",{className:"room-list"},t)}},{key:"render",value:function(){var e,t,a=this;e=this.state.creatingRoom?this.renderCreateRoomForm():this.renderRoomList();var n="hide";return"room-waiting-page"===this.state.nextPage?t=r.a.createElement(v,{appUtils:this.props.appUtils,goBackPrevPage:this.goBackThisPage,roomId:this.nextRoomId}):n=void 0,r.a.createElement("div",{className:"full-size"},r.a.createElement("div",{id:"room-page",className:n},r.a.createElement("div",{id:"room-page-select-mode"},r.a.createElement("button",{id:"room-page-normal-mode-button",className:"clickable",onClick:function(){a.setRoomMode(1)}},"\u4e00\u822c\u6a21\u5f0f"),r.a.createElement("button",{id:"room-page-ladder-mode-button",className:"clickable",onClick:function(){a.setRoomMode(2)}},"\u5929\u68af\u6a21\u5f0f")),r.a.createElement("div",{className:"content-window"},e)),t)}}]),t}(r.a.Component),k=function(e){function t(e){var a;return Object(n.a)(this,t),(a=Object(l.a)(this,Object(u.a)(t).call(this,e))).state={},a.props.appUtils.serverSide.addListener("card-pool",function(e){if("gameLogicEngineMessage"===e.type){var t=e.data;"accountSystem"===t.eventType&&"drawCards"===t.function&&(t.returnValue.success?a.props.appUtils.promptDialog("info","\u62bd\u5361\u6210\u529f\ud83d\ude0f~\n\u62bd\u5361\u5f35\u6578:".concat(t.returnValue.amount,"\n\u5269\u9918\u984d\u5ea6:").concat(t.returnValue.money)):a.props.appUtils.promptDialog("error","\u62bd\u5361\u5931\u6557\ud83d\ude30"))}}),a.drawCards=a.drawCards.bind(Object(d.a)(a)),a.props.appUtils.setGoBackHandler(a.props.goBackPrevPage),a}return Object(p.a)(t,e),Object(c.a)(t,[{key:"drawCards",value:function(e){this.props.appUtils.serverSide.send({eventType:"accountSystem",function:"drawCards",params:[e]})}},{key:"render",value:function(){var e=this;return r.a.createElement("div",{id:"card-pool-page"},r.a.createElement("div",{className:"button-container"},r.a.createElement("button",{key:100,className:"clickable",onClick:function(){e.drawCards(100)}},r.a.createElement("span",{role:"img","aria-label":"green-checked"},"\u2705\u4e00\u6642\u62bd\u5361\u4e00\u6642\u723d\u2705",r.a.createElement("br",null),"1\u5f35100")),r.a.createElement("button",{key:1e3,className:"clickable",onClick:function(){e.drawCards(1e3)}},r.a.createElement("span",{role:"img","aria-label":"heart"},"\ud83e\udde1\u4e00\u76f4\u62bd\u5361\u4e00\u76f4\u723d\ud83e\udde1",r.a.createElement("br",null),"11\u5f351000"))))}}]),t}(r.a.Component),y=function(e){function t(e){var a;return Object(n.a)(this,t),(a=Object(l.a)(this,Object(u.a)(t).call(this,e))).state={},a.props.appUtils.serverSide.addListener("modify-cards",function(e){if("gameLogicEngineMessage"===e.type){var t=e.data;"accountSystem"===t.eventType&&("getCards"!==t.function&&"modifyCards"!==t.function||a.setState(function(e){return Object.assign(e,{deck:Object(h.a)(t.returnValue.deck).sort(function(e,t){return e-t}),amounts:t.returnValue.amounts,cards:Object(h.a)(t.returnValue.cards).sort(function(e,t){return e-t})})}))}}),a.getCards=a.getCards.bind(Object(d.a)(a)),a.modifyCards=a.modifyCards.bind(Object(d.a)(a)),a.props.appUtils.setGoBackHandler(a.props.goBackPrevPage),a.getCards(),a}return Object(p.a)(t,e),Object(c.a)(t,[{key:"getCards",value:function(){this.props.appUtils.serverSide.send({eventType:"accountSystem",function:"getCards",params:[this.props.appUtils.getUserInfo().userId]})}},{key:"modifyCards",value:function(){for(var e=Object(h.a)(this.state.cards),t=0;t<e.length;++t){var a=Math.floor(Math.random()*e.length),n=[e[a],e[t]];e[t]=n[0],e[a]=n[1]}this.props.appUtils.serverSide.send({eventType:"accountSystem",function:"modifyCards",params:[this.props.appUtils.getUserInfo().userId],deck:e.splice(0,30)})}},{key:"render",value:function(){var e=[r.a.createElement("p",{key:"deck"},"\u724c\u7d44: ",this.state.deck&&this.state.deck.join(", ")),r.a.createElement("p",{key:"amount"},"\u5361\u7247\u7e3d\u6578: ",this.state.amounts||""),r.a.createElement("p",{key:"cards"},"\u6240\u6709\u5361\u724c: ",this.state.cards&&this.state.cards.join(", "))];return r.a.createElement("div",{className:"full-size"},r.a.createElement("div",{id:"modify-cards-page"},r.a.createElement("div",{className:"content-container"},r.a.createElement("div",{key:"cards-info",className:"cards-info"},e),r.a.createElement("div",{key:"button-container",className:"button-container"},r.a.createElement("button",{className:"clickable",onClick:this.modifyCards},r.a.createElement("span",{role:"img","aria-label":"dice"},"\ud83c\udfb2"),"\u96a8\u6a5f\u7d44\u724c")))))}}]),t}(r.a.Component),O=function(e){function t(e){var a;return Object(n.a)(this,t),(a=Object(l.a)(this,Object(u.a)(t).call(this,e))).state={playerInfo:null},a.props.appUtils.serverSide.addListener("player-info",function(e){if("gameLogicEngineMessage"===e.type){var t=e.data;if("accountSystem"===t.eventType)if("getAccountInfo"===t.function){if(t.returnValue.success){var n=a.props.appUtils.getUserInfo().userId,o=t.returnValue[n];a.setState(function(e){return Object.assign(e,{playerInfo:{userId:n,username:o.accountName,money:o.money,ladderPoint:o.ladderPoint,ladderLevel:o.ladderLevel,win:o.win,lose:o.lose,level:o.level,exp:o.exp}})})}}else"payMoney"===t.function&&a.sendPlayerInfoPacket()}}),a.sendPlayerInfoPacket=a.sendPlayerInfoPacket.bind(Object(d.a)(a)),a.sendPlayerInfoPacket(),a}return Object(p.a)(t,e),Object(c.a)(t,[{key:"sendPlayerInfoPacket",value:function(){this.props.appUtils.serverSide.send({eventType:"accountSystem",function:"getAccountInfo",params:[this.props.appUtils.getUserInfo().userId]}),this.props.appUtils.setGoBackHandler(this.props.goBackPrevPage)}},{key:"getMoney",value:function(e){this.props.appUtils.serverSide.send({eventType:"accountSystem",function:"payMoney",params:[e]})}},{key:"render",value:function(){var e=this,t=this.state.playerInfo;return r.a.createElement("div",{className:"full-size"},r.a.createElement("div",{id:"player-info-page"},r.a.createElement("div",{className:"get-money-container"},r.a.createElement("button",{id:"100",className:"clickable",onClick:function(){e.getMoney(100)}},"\u6c2a\u91d1100\u5143!!"),r.a.createElement("button",{id:"500",className:"clickable",onClick:function(){e.getMoney(500)}},"\u6c2a\u91d1500\u5143!!"),r.a.createElement("button",{id:"1000",className:"clickable",onClick:function(){e.getMoney(1e3)}},"\u6c2a\u91d11000\u5143!!")),r.a.createElement("div",{className:"info-container"},r.a.createElement("ul",null,r.a.createElement("li",{key:"username"},"\u5e33\u865f: ",t&&t.username),r.a.createElement("li",{key:"userId"},"ID: ",t&&t.userId),r.a.createElement("li",{key:"exp"},"\u7d93\u9a57\u503c: ",t&&t.exp),r.a.createElement("li",{key:"money"},"\u984d\u5ea6: ",t&&t.money),r.a.createElement("li",{key:"level"},"\u7b49\u7d1a: ",t&&t.level),r.a.createElement("li",{key:"win"},"\u52dd\u5c40: ",t&&t.win),r.a.createElement("li",{key:"lose"},"\u6557\u5c40: ",t&&t.lose),r.a.createElement("li",{key:"ladderPoint"},"\u5929\u68af\u7a4d\u5206: ",t&&t.ladderPoint),r.a.createElement("li",{key:"ladderLevel"},"\u5929\u68af\u7b49\u7d1a: ",t&&t.ladderLevel)))))}}]),t}(r.a.Component),E=function(e){function t(e){var a;return Object(n.a)(this,t),(a=Object(l.a)(this,Object(u.a)(t).call(this,e))).state={},a.handleSendMessage=a.handleSendMessage.bind(Object(d.a)(a)),a.props.appUtils.setGoBackHandler(a.props.goBackPrevPage),a}return Object(p.a)(t,e),Object(c.a)(t,[{key:"handleSendMessage",value:function(){var e=parseInt(document.getElementById("chat-send-to").value,10)||0,t=document.getElementById("chat-message").value.toString().trim();document.getElementById("chat-message").value="",this.props.appUtils.serverSide.sendRawObject({time:Date.now(),userId:this.props.appUtils.getUserInfo().userId,type:"chat",data:{from:this.props.appUtils.getUserInfo().userId,to:e,message:t}})}},{key:"render",value:function(){return r.a.createElement("div",{id:"chat-page"},r.a.createElement("div",{className:"content-container"},r.a.createElement(m,{labelText:"\u50b3\u9001\u81f3(userId):",id:"chat-send-to",type:"text"}),r.a.createElement(m,{labelText:"\u8a0a\u606f:",id:"chat-message",type:"text"}),r.a.createElement("button",{className:"clickable",onClick:this.handleSendMessage},"\u50b3\u9001")))}}]),t}(r.a.Component),j=function(e){function t(e){var a;return Object(n.a)(this,t),(a=Object(l.a)(this,Object(u.a)(t).call(this,e))).state={nextPage:null},a.goBackThisPage=a.goBackThisPage.bind(Object(d.a)(a)),a.props.appUtils.setGoBackHandler(a.props.goBackPrevPage),a.props.appUtils.serverSide.addListener("chat",function(e){if("chat"===e.type){var t="\u3010\u804a\u5929\u5ba4\u8a0a\u606f\u3011\n\u4f86\u81ea(userId): ".concat(e.data.from,"\n\u8a0a\u606f: ").concat(e.data.message);a.props.appUtils.promptDialog("info",t)}}),a.props.appUtils.playBgm("bgmNormal"),a}return Object(p.a)(t,e),Object(c.a)(t,[{key:"goBackThisPage",value:function(){this.setState(function(e){return Object.assign(e,{nextPage:null})}),this.props.appUtils.setGoBackHandler(this.props.goBackPrevPage)}},{key:"render",value:function(){var e,t=this,a="hide";return"room"===this.state.nextPage?e=r.a.createElement(b,{appUtils:this.props.appUtils,goBackPrevPage:this.goBackThisPage}):"card-pool"===this.state.nextPage?e=r.a.createElement(k,{appUtils:this.props.appUtils,goBackPrevPage:this.goBackThisPage}):"modify-cards"===this.state.nextPage?e=r.a.createElement(y,{appUtils:this.props.appUtils,goBackPrevPage:this.goBackThisPage}):"player-info"===this.state.nextPage?e=r.a.createElement(O,{appUtils:this.props.appUtils,goBackPrevPage:this.goBackThisPage}):"chat"===this.state.nextPage?e=r.a.createElement(E,{appUtils:this.props.appUtils,goBackPrevPage:this.goBackThisPage}):a=void 0,r.a.createElement("div",{className:"full-size"},r.a.createElement("div",{id:"lobby-page",className:a},r.a.createElement("div",{className:"button-container"},r.a.createElement("button",{key:1,className:"clickable",onClick:function(){t.setState(function(e){return Object.assign(e,{nextPage:"room"})})}},"\u9078\u64c7\u5c0d\u6230\u6a21\u5f0f"),r.a.createElement("button",{key:2,className:"clickable",onClick:function(){t.setState(function(e){return Object.assign(e,{nextPage:"card-pool"})})}},"\u5361\u6c60"),r.a.createElement("button",{key:3,className:"clickable",onClick:function(){t.setState(function(e){return Object.assign(e,{nextPage:"modify-cards"})})}},"\u4fee\u6539\u6392\u7d44"),r.a.createElement("button",{key:4,className:"clickable",onClick:function(){t.setState(function(e){return Object.assign(e,{nextPage:"player-info"})})}},"\u73a9\u5bb6\u8cc7\u8a0a"),r.a.createElement("button",{key:5,className:"clickable",onClick:function(){t.setState(function(e){return Object.assign(e,{nextPage:"chat"})})}},"\u804a\u5929\u5ba4"))),e)}}]),t}(r.a.Component),I=function(e){function t(e){var a;return Object(n.a)(this,t),(a=Object(l.a)(this,Object(u.a)(t).call(this,e))).state={nextPage:null},a.serverSide=a.props.appUtils.serverSide,a.handleSubmit=a.handleSubmit.bind(Object(d.a)(a)),a.handleRegister=a.handleRegister.bind(Object(d.a)(a)),a.goBackThisPage=a.goBackThisPage.bind(Object(d.a)(a)),a.serverSide.addListener("login-page",function(e){if(a.state.nextPage||"gameLogicEngineMessage"===e.type){var t=e.data;if("accountSystem"===t.eventType&&"createAccount"===t.function){var n="\u5efa\u7acb\u5e33\u865f".concat(t.returnValue.success?"\u6210\u529f! \ud83c\udf89\ud83c\udf89\ud83c\udf89":"\u5931\u6557!\n\u53ef\u80fd\u7684\u539f\u56e0: \u4e0d\u5408\u6cd5\u7684\u5e33\u865f\u6216\u5bc6\u78bc\u6216\u662f\u5df2\u7d93\u6709\u6b64\u4f7f\u7528\u8005");a.props.appUtils.promptDialog(t.returnValue.success?"info":"error",n)}else"accountSystem"===t.eventType&&"login"===t.function&&t.returnValue.success&&(document.getElementById("input-password").value="",a.props.appUtils.setUserInfo({userId:t.returnValue.userId}),a.setState(function(e){return Object.assign({},e,{nextPage:"lobby"})}))}}),a.props.appUtils.setGoBackHandler(null),a}return Object(p.a)(t,e),Object(c.a)(t,[{key:"handleSubmit",value:function(e){this.serverSide.send({eventType:"accountSystem",function:"login",params:[e.username,e.password]})}},{key:"handleRegister",value:function(e){this.serverSide.send({eventType:"accountSystem",function:"createAccount",params:[e.username,e.password]})}},{key:"goBackThisPage",value:function(){window.location.reload()}},{key:"render",value:function(){var e,t="hide";return"lobby"===this.state.nextPage?t=r.a.createElement(j,{appUtils:this.props.appUtils,goBackPrevPage:this.goBackThisPage}):e=void 0,r.a.createElement("div",{className:"full-size"},r.a.createElement("div",{id:"login-page",className:e},r.a.createElement("h1",null,r.a.createElement("span",null,"Another"),r.a.createElement("span",null,"Card"),r.a.createElement("span",null,"Game")),r.a.createElement(P,{onSubmit:this.handleSubmit,onRegister:this.handleRegister,promptDialog:this.props.appUtils.promptDialog})),t)}}]),t}(r.a.Component),P=function(e){function t(e){var a;return Object(n.a)(this,t),(a=Object(l.a)(this,Object(u.a)(t).call(this,e))).handleSubmit=a.handleSubmit.bind(Object(d.a)(a)),a.handleRegister=a.handleRegister.bind(Object(d.a)(a)),a}return Object(p.a)(t,e),Object(c.a)(t,[{key:"handleSubmit",value:function(e){e.preventDefault(),this.props.onSubmit({username:document.getElementById("input-account").value,password:document.getElementById("input-password").value})}},{key:"handleRegister",value:function(e){var t=this;e.preventDefault();var a=document.getElementById("input-account").value,n=document.getElementById("input-password").value,o="\u5e33\u865f: ".concat(a,"\n")+"\u5bc6\u78bc: ".concat("*".repeat(n.length));this.props.promptDialog("info","\u8acb\u5148\u95b1\u8b80\u4e26\u540c\u610f\u4ee5\u4e0b\u4f7f\u7528\u689d\u6b3e:\n\u672c\u904a\u6232\u4e0d\u6703\u64c5\u81ea\u5728\u60a8\u672a\u6388\u6b0a\u7684\u60c5\u6cc1\u4e0b\uff0c\u5c07\u60a8\u7684\u500b\u4eba\u8cc7\u6599\u7d93\u7531\u6563\u4f48\u3001\u62cd\u8ce3\u7b49\u65b9\u5f0f\u79fb\u4ea4\u7d66\u7b2c\u4e09\u8005\uff0c\u56e0\u70ba\u6211\u5011\u61f6\u5f97\u505a\ud83d\ude44\u3002",function(){t.props.promptDialog("info","\u78ba\u5b9a\u9f41\ud83e\udd14\ud83e\udd14?\n".concat(o),function(){t.props.onRegister({username:a,password:n})})})}},{key:"render",value:function(){return r.a.createElement("form",{id:"login-form"},r.a.createElement(m,{labelText:"\u5e33\u865f",id:"input-account",type:"text",autoComplete:"username"}),r.a.createElement(m,{labelText:"\u5bc6\u78bc",id:"input-password",type:"password",autoComplete:"current-password"}),r.a.createElement("input",{type:"submit",value:"\u767b\u5165",onClick:this.handleSubmit,className:"clickable"}),r.a.createElement("button",{onClick:this.handleRegister,className:"clickable"},"\u8a3b\u518a"))}}]),t}(r.a.Component),B=I,S=function(e){function t(e){var a;return Object(n.a)(this,t),(a=Object(l.a)(this,Object(u.a)(t).call(this,e))).state={goBackHandler:null},a.goBackHandler=a.goBackHandler.bind(Object(d.a)(a)),a.setGoBackHandler=a.setGoBackHandler.bind(Object(d.a)(a)),a.props.returnSetGoBackHandlerFun(a.setGoBackHandler),a}return Object(p.a)(t,e),Object(c.a)(t,[{key:"setGoBackHandler",value:function(e){this.setState(function(t){return Object.assign(t,{goBackHandler:e})})}},{key:"goBackHandler",value:function(){this.state.goBackHandler&&this.state.goBackHandler()}},{key:"render",value:function(){return r.a.createElement("div",{id:"go-back-button-container"},r.a.createElement("button",{className:"clickable",onClick:this.goBackHandler},"\u2190"))}}]),t}(r.a.Component),U=function(e){function t(){return Object(n.a)(this,t),Object(l.a)(this,Object(u.a)(t).apply(this,arguments))}return Object(p.a)(t,e),Object(c.a)(t,[{key:"render",value:function(){var e={info:"\u8a0a\u606f",warning:"\u8b66\u544a",error:"\u932f\u8aa4"}[this.props.type];return r.a.createElement("div",{className:"dialog-container"},r.a.createElement("div",{className:"dialog"},r.a.createElement("span",{className:"dialog-title"},e),r.a.createElement("hr",null),r.a.createElement("div",{className:"dialog-message"},this.props.message),r.a.createElement("span",{className:"button-container"},r.a.createElement("button",{onClick:this.props.onOk,className:"clickable"},"\u78ba\u8a8d"))))}}]),t}(r.a.Component),w=function(e){function t(e){var a;return Object(n.a)(this,t),(a=Object(l.a)(this,Object(u.a)(t).call(this,e))).state={},a.state.dialogs=[],a.lastDialogIndex=0,a.promptDialog=a.promptDialog.bind(Object(d.a)(a)),e.returnPromptDialogFun&&e.returnPromptDialogFun(a.promptDialog),a}return Object(p.a)(t,e),Object(c.a)(t,[{key:"promptDialog",value:function(e,t){var a=this,n=arguments.length>2&&void 0!==arguments[2]?arguments[2]:null;this.setState(function(o){return(o=Object(g.a)({},o)).dialogs.push({dialogId:++a.lastDialogIndex,type:e,message:t,callback:n}),o})}},{key:"handleClearDialog",value:function(e){this.setState(function(t){for(var a=0;a<t.dialogs.length;++a)t.dialogs[a].dialogId===e&&t.dialogs.splice(a,1);return t})}},{key:"render",value:function(){for(var e=this,t=[],a=function(a){var n=e.state.dialogs[a];t.push(r.a.createElement(U,{key:n.dialogId,type:n.type,message:n.message,onOk:function(){e.handleClearDialog(n.dialogId),n.callback&&n.callback()}}))},n=0;n<this.state.dialogs.length;++n)a(n);return r.a.createElement("div",{id:"dialog-container"},t)}}]),t}(r.a.Component),C=a(36),N=a.n(C),R=function(){function e(t){var a=this;Object(n.a)(this,e),this.serverPort=t.port,this.listeners={},this.userId=0,this.io=N()(":"+this.serverPort),this.io.on("dataToClient",function(e){for(var t in window.logger.debug("from server:\n".concat(JSON.stringify(e,null,2))),a.listeners)a.listeners[t](e)})}return Object(c.a)(e,[{key:"addListener",value:function(e,t){this.listeners[e]=t}},{key:"removeListener",value:function(e){delete this.listeners[e]}},{key:"setUserId",value:function(e){e<=0&&(e=0),this.userId=e}},{key:"send",value:function(e){this.sendRawObject({time:Date.now(),type:"gameLogicEngineMessage",userId:this.userId,data:e})}},{key:"sendRawObject",value:function(e){this.io.emit("dataToServer",e)}}]),e}(),x=function(e){function t(e){var a;for(var o in Object(n.a)(this,t),(a=Object(l.a)(this,Object(u.a)(t).call(this,e))).state={},a.promptDialog=null,a.setGoBackHandler=function(){},a.userInfo={userId:0,userName:""},a.serverSide=new R({port:3456}),a.getUserInfo=a.getUserInfo.bind(Object(d.a)(a)),a.setUserInfo=a.setUserInfo.bind(Object(d.a)(a)),a.playBgm=a.playBgm.bind(Object(d.a)(a)),a.appUtils={serverSide:a.serverSide,getUserInfo:a.getUserInfo,setUserInfo:a.setUserInfo,promptDialog:function(){var e;return(e=a).promptDialog.apply(e,arguments)},setGoBackHandler:function(){var e;return(e=a).setGoBackHandler.apply(e,arguments)},playBgm:a.playBgm},a.audio={clickSound:new Audio("click-sound.wav"),bgmNormal:new Audio("bgm-normal.mp3"),bgmBattle:new Audio("bgm-battle.mp3")},a.audio)o.startsWith("bgm")&&(a.audio[o].volume=.3,a.audio[o].loop=!0);var r=document.getElementById("app");return window.addEventListener("click",function(e){for(var t=e.target;t&&t!==r;){if(t.classList.contains("clickable")){a.audio.clickSound.currentTime=0,a.audio.clickSound.play();break}t=t.parentElement}}),a}return Object(p.a)(t,e),Object(c.a)(t,[{key:"getUserInfo",value:function(){return this.userInfo}},{key:"setUserInfo",value:function(e){this.userInfo="function"===typeof e?e(this.getUserInfo):e,this.serverSide.setUserId(this.userInfo.userId)}},{key:"playBgm",value:function(e){for(var t in this.audio)this.audio[t].pause(),this.audio[t].currentTime=0,t===e&&this.audio[e].play()}},{key:"render",value:function(){var e=this;return r.a.createElement("div",{id:"app"},r.a.createElement(B,{appUtils:this.appUtils}),r.a.createElement(S,{returnSetGoBackHandlerFun:function(t){e.setGoBackHandler=t}}),r.a.createElement(w,{returnPromptDialogFun:function(t){e.promptDialog=t}}))}}]),t}(r.a.Component),T={};T.Logger=function(){function e(){var t=arguments.length>0&&void 0!==arguments[0]?arguments[0]:{};Object(n.a)(this,e),this.console=t.console||window.console,this.levelOrder=["debug","info","warn","error"],this.level=this.levelOrder.indexOf(t.level),this.level<0&&(this.level=this.levelOrder.length-1)}return Object(c.a)(e,[{key:"log",value:function(e){this.console.log(e)}},{key:"debug",value:function(e){this.level>=this.levelOrder.indexOf("debug")&&this.console.debug("[DEBUG] ".concat(e))}},{key:"info",value:function(e){this.level>=this.levelOrder.indexOf("info")&&this.console.info("[INFO] ".concat(e))}},{key:"warn",value:function(e){this.level>=this.levelOrder.indexOf("warn")&&this.console.warn("[WARN] ".concat(e))}},{key:"error",value:function(e){this.level>=this.levelOrder.indexOf("error")&&this.console.error("[ERROR] ".concat(e))}}]),e}(),T.calculateRem=function(e,t){var a=e||document.documentElement.clientWidth,n=t||document.documentElement.clientHeight;return 9*a<16*n?a/32:n/18},T.adjustWindowSize=function(){document.documentElement.style.fontSize="".concat(T.calculateRem(),"px")};var L=T,M=function e(){Object(n.a)(this,e),window.logger=new L.Logger,L.adjustWindowSize(),window.addEventListener("orientationchange",L.adjustWindowSize),window.addEventListener("resize",L.adjustWindowSize),this.app=i.a.render(r.a.createElement(x,null),document.getElementById("root"))};window.acgAppController=new M,"serviceWorker"in navigator&&navigator.serviceWorker.ready.then(function(e){e.unregister()})}},[[37,1,2]]]);
//# sourceMappingURL=main.0186ba51.chunk.js.map