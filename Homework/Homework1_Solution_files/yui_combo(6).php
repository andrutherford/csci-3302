/*
YUI 3.17.2 (build 9c3c78e)
Copyright 2014 Yahoo! Inc. All rights reserved.
Licensed under the BSD License.
http://yuilibrary.com/license/
*/

YUI.add("anim-base",function(e,t){var n="running",r="startTime",i="elapsedTime",s="start",o="tween",u="end",a="node",f="paused",l="reverse",c="iterationCount",h=Number,p={},d;e.Anim=function(){e.Anim.superclass.constructor.apply(this,arguments),e.Anim._instances[e.stamp(this)]=this},e.Anim.NAME="anim",e.Anim._instances={},e.Anim.RE_DEFAULT_UNIT=/^width|height|top|right|bottom|left|margin.*|padding.*|border.*$/i,e.Anim.DEFAULT_UNIT="px",e.Anim.DEFAULT_EASING=function(e,t,n,r){return n*e/r+t},e.Anim._intervalTime=20,e.Anim.behaviors={left:{get:function(e,t){return e._getOffset(t)}}},e.Anim.behaviors.top=e.Anim.behaviors.left,e.Anim.DEFAULT_SETTER=function(t,n,r,i,s,o,u,a){var f=t._node,l=f._node,c=u(s,h(r),h(i)-h(r),o);l?"style"in l&&(n in l.style||n in e.DOM.CUSTOM_STYLES)?(a=a||"",f.setStyle(n,c+a)):"attributes"in l&&n in l.attributes?f.setAttribute(n,c):n in l&&(l[n]=c):f.set?f.set(n,c):n in f&&(f[n]=c)},e.Anim.DEFAULT_GETTER=function(t,n){var r=t._node,i=r._node,s="";return i?"style"in i&&(n in i.style||n in e.DOM.CUSTOM_STYLES)?s=r.getComputedStyle(n):"attributes"in i&&n in i.attributes?s=r.getAttribute(n):n in i&&(s=i[n]):r.get?s=r.get(n):n in r&&(s=r[n]),s},e.Anim.ATTRS={node:{setter:function(t){return t&&(typeof t=="string"||t.nodeType)&&(t=e.one(t)),this._node=t,!t,t}},duration:{value:1},easing:{value:e.Anim.DEFAULT_EASING,setter:function(t){if(typeof t=="string"&&e.Easing)return e.Easing[t]}},from:{},to:{},startTime:{value:0,readOnly:!0},elapsedTime:{value:0,readOnly:!0},running:{getter:function(){return!!p[e.stamp(this)]},value:!1,readOnly:!0},iterations:{value:1},iterationCount:{value:0,readOnly:!0},direction:{value:"normal"},paused:{readOnly:!0,value:!1},reverse:{value:!1}},e.Anim.run=function(){var t=e.Anim._instances,n;for(n in t)t[n].run&&t[n].run()},e.Anim.pause=function(){for(var t in p)p[t].pause&&p[t].pause();e.Anim._stopTimer()},e.Anim.stop=function(){for(var t in p)p[t].stop&&p[t].stop();e.Anim._stopTimer()},e.Anim._startTimer=function(){d||(d=setInterval(e.Anim._runFrame,e.Anim._intervalTime))},e.Anim._stopTimer=function(){clearInterval(d),d=0},e.Anim._runFrame=function(){var t=!0,n;for(n in p)p[n]._runFrame&&(t=!1,p[n]._runFrame());t&&e.Anim._stopTimer()},e.Anim.RE_UNITS=/^(-?\d*\.?\d*){1}(em|ex|px|in|cm|mm|pt|pc|%)*$/;var v={run:function(){return this.get(f)?this._resume():this.get(n)||this._start(),this},pause:function(){return this.get(n)&&this._pause(),this},stop:function(e){return(this.get(n)||this.get(f))&&this._end(e),this},_added:!1,_start:function(){this._set(r,new Date-this.get(i)),this._actualFrames=0,this.get(f)||this._initAnimAttr(),p[e.stamp(this)]=this,e.Anim._startTimer(),this.fire(s)},_pause:function(){this._set(r,null),this._set(f,!0),delete p[e.stamp(this)],this.fire("pause")},_resume:function(){this._set(f,!1),p[e.stamp(this)]=this,this._set(r,new Date-this.get(i)),e.Anim._startTimer(),this.fire("resume")},_end:function(t){var n=this.get("duration")*1e3;t&&this._runAttrs(n,n,this.get(l)),this._set(r,null),this._set(i,0),this._set(f,!1),delete p[e.stamp(this)],this.fire(u,{elapsed:this.get(i)})},_runFrame:function(){var e=this._runtimeAttr.duration,t=new Date-this.get(r),n=this.get(l),s=t>=e;this._runAttrs(t,e,n),this._actualFrames+=1,this._set(i,t),this.fire(o),s&&this._lastFrame()},_runAttrs:function(t,n,r){var i=this._runtimeAttr,s=e.Anim.behaviors,o=i.easing,u=n,a=!1,f,l,c;t>=n&&(a=!0),r&&(t=n-t,u=0);for(c in i)i[c].to&&(f=i[c],l=c in s&&"set"in s[c]?s[c].set:e.Anim.DEFAULT_SETTER,a?l(this,c,f.from,f.to,u,n,o,f.unit):l(this,c,f.from,f.to,t,n,o,f.unit))},_lastFrame:function(){var e=this.get("iterations"),t=this.get(c);t+=1,e==="infinite"||t<e?(this.get("direction")==="alternate"&&this.set(l,!this.get(l)),this.fire("iteration")):(t=0,this._end()),this._set(r,new Date),this._set(c,t)},_initAnimAttr:function(){var t=this.get("from")||{},n=this.get("to")||{},r={duration:this.get("duration")*1e3,easing:this.get("easing")},i=e.Anim.behaviors,s=this.get(a),o,u,f;e.each(n,function(n,a){typeof n=="function"&&(n=n.call(this,s)),u=t[a],u===undefined?u=a in i&&"get"in i[a]?i[a].get(this,a):e.Anim.DEFAULT_GETTER(this,a):typeof u=="function"&&(u=u.call(this,s));var l=e.Anim.RE_UNITS.exec(u),c=e.Anim.RE_UNITS.exec(n);u=l?l[1]:u,f=c?c[1]:n,o=c?c[2]:l?l[2]:"",!o&&e.Anim.RE_DEFAULT_UNIT.test(a)&&(o=e.Anim.DEFAULT_UNIT);if(!u||!f){e.error('invalid "from" or "to" for "'+a+'"',"Anim");return}r[a]={from:e.Lang.isObject(u)?e.clone(u):u,to:f,unit:o}},this),this._runtimeAttr=r},_getOffset:function(e){var t=this._node,n=t.getComputedStyle(e),r=e==="left"?"getX":"getY",i=e==="left"?"setX":"setY",s;return n==="auto"&&(s=t.getStyle("position"),s==="absolute"||s==="fixed"?(n=t[r](),t[i](n)):n=0),n},destructor:function(){delete e.Anim._instances[e.stamp(this)]}};e.extend(e.Anim,e.Base,v)},"3.17.2",{requires:["base-base","node-style","color-base"]});
/*
YUI 3.17.2 (build 9c3c78e)
Copyright 2014 Yahoo! Inc. All rights reserved.
Licensed under the BSD License.
http://yuilibrary.com/license/
*/

YUI.add("anim-color",function(e,t){var n=Number;e.Anim.getUpdatedColorValue=function(t,r,i,s,o){return t=e.Color.re_RGB.exec(e.Color.toRGB(t)),r=e.Color.re_RGB.exec(e.Color.toRGB(r)),(!t||t.length<3||!r||r.length<3)&&e.error("invalid from or to passed to color behavior"),"rgb("+[Math.floor(o(i,n(t[1]),n(r[1])-n(t[1]),s)),Math.floor(o(i,n(t[2]),n(r[2])-n(t[2]),s)),Math.floor(o(i,n(t[3]),n(r[3])-n(t[3]),s))].join(", ")+")"},e.Anim.behaviors.color={set:function(t,n,r,i,s,o,u){t._node.setStyle(n,e.Anim.getUpdatedColorValue(r,i,s,o,u))},get:function(e,t){var n=e._node.getComputedStyle(t);return n=n==="transparent"?"rgb(255, 255, 255)":n,n}},e.each(["backgroundColor","borderColor","borderTopColor","borderRightColor","borderBottomColor","borderLeftColor"],function(t){e.Anim.behaviors[t]=e.Anim.behaviors.color})},"3.17.2",{requires:["anim-base"]});
/*
YUI 3.17.2 (build 9c3c78e)
Copyright 2014 Yahoo! Inc. All rights reserved.
Licensed under the BSD License.
http://yuilibrary.com/license/
*/

YUI.add("anim-xy",function(e,t){var n=Number;e.Anim.behaviors.xy={set:function(e,t,r,i,s,o,u){e._node.setXY([u(s,n(r[0]),n(i[0])-n(r[0]),o),u(s,n(r[1]),n(i[1])-n(r[1]),o)])},get:function(e){return e._node.getXY()}}},"3.17.2",{requires:["anim-base","node-screen"]});
/*
YUI 3.17.2 (build 9c3c78e)
Copyright 2014 Yahoo! Inc. All rights reserved.
Licensed under the BSD License.
http://yuilibrary.com/license/
*/

YUI.add("anim-curve",function(e,t){e.Anim.behaviors.curve={set:function(t,n,r,i,s,o,u){r=r.slice.call(r),i=i.slice.call(i);var a=u(s,0,100,o)/100;i.unshift(r),t._node.setXY(e.Anim.getBezier(i,a))},get:function(e){return e._node.getXY()}},e.Anim.getBezier=function(e,t){var n=e.length,r=[],i,s;for(i=0;i<n;++i)r[i]=[e[i][0],e[i][1]];for(s=1;s<n;++s)for(i=0;i<n-s;++i)r[i][0]=(1-t)*r[i][0]+t*r[parseInt(i+1,10)][0],r[i][1]=(1-t)*r[i][1]+t*r[parseInt(i+1,10)][1];return[r[0][0],r[0][1]]}},"3.17.2",{requires:["anim-xy"]});
/*
YUI 3.17.2 (build 9c3c78e)
Copyright 2014 Yahoo! Inc. All rights reserved.
Licensed under the BSD License.
http://yuilibrary.com/license/
*/

YUI.add("anim-easing",function(e,t){var n={easeNone:function(e,t,n,r){return n*e/r+t},easeIn:function(e,t,n,r){return n*(e/=r)*e+t},easeOut:function(e,t,n,r){return-n*(e/=r)*(e-2)+t},easeBoth:function(e,t,n,r){return(e/=r/2)<1?n/2*e*e+t:-n/2*(--e*(e-2)-1)+t},easeInStrong:function(e,t,n,r){return n*(e/=r)*e*e*e+t},easeOutStrong:function(e,t,n,r){return-n*((e=e/r-1)*e*e*e-1)+t},easeBothStrong:function(e,t,n,r){return(e/=r/2)<1?n/2*e*e*e*e+t:-n/2*((e-=2)*e*e*e-2)+t},elasticIn:function(e,t,n,r,i,s){var o;return e===0?t:(e/=r)===1?t+n:(s||(s=r*.3),!i||i<Math.abs(n)?(i=n,o=s/4):o=s/(2*Math.PI)*Math.asin(n/i),-(i*Math.pow(2,10*(e-=1))*Math.sin((e*r-o)*2*Math.PI/s))+t)},elasticOut:function(e,t,n,r,i,s){var o;return e===0?t:(e/=r)===1?t+n:(s||(s=r*.3),!i||i<Math.abs(n)?(i=n,o=s/4):o=s/(2*Math.PI)*Math.asin(n/i),i*Math.pow(2,-10*e)*Math.sin((e*r-o)*2*Math.PI/s)+n+t)},elasticBoth:function(e,t,n,r,i,s){var o;return e===0?t:(e/=r/2)===2?t+n:(s||(s=r*.3*1.5),!i||i<Math.abs(n)?(i=n,o=s/4):o=s/(2*Math.PI)*Math.asin(n/i),e<1?-0.5*i*Math.pow(2,10*(e-=1))*Math.sin((e*r-o)*2*Math.PI/s)+t:i*Math.pow(2,-10*(e-=1))*Math.sin((e*r-o)*2*Math.PI/s)*.5+n+t)},backIn:function(e,t,n,r,i){return i===undefined&&(i=1.70158),e===r&&(e-=.001),n*(e/=r)*e*((i+1)*e-i)+t},backOut:function(e,t,n,r,i){return typeof i=="undefined"&&(i=1.70158),n*((e=e/r-1)*e*((i+1)*e+i)+1)+t},backBoth:function(e,t,n,r,i){return typeof i=="undefined"&&(i=1.70158),(e/=r/2)<1?n/2*e*e*(((i*=1.525)+1)*e-i)+t:n/2*((e-=2)*e*(((i*=1.525)+1)*e+i)+2)+t},bounceIn:function(t,n,r,i){return r-e.Easing.bounceOut(i-t,0,r,i)+n},bounceOut:function(e,t,n,r){return(e/=r)<1/2.75?n*7.5625*e*e+t:e<2/2.75?n*(7.5625*(e-=1.5/2.75)*e+.75)+t:e<2.5/2.75?n*(7.5625*(e-=2.25/2.75)*e+.9375)+t:n*(7.5625*(e-=2.625/2.75)*e+.984375)+t},bounceBoth:function(t,n,r,i){return t<i/2?e.Easing.bounceIn(t*2,0,r,i)*.5+n:e.Easing.bounceOut(t*2-i,0,r,i)*.5+r*.5+n}};e.Easing=n},"3.17.2",{requires:["anim-base"]});
/*
YUI 3.17.2 (build 9c3c78e)
Copyright 2014 Yahoo! Inc. All rights reserved.
Licensed under the BSD License.
http://yuilibrary.com/license/
*/

YUI.add("anim-node-plugin",function(e,t){var n=function(t){t=t?e.merge(t):{},t.node=t.host,n.superclass.constructor.apply(this,arguments)};n.NAME="nodefx",n.NS="fx",e.extend(n,e.Anim),e.namespace("Plugin"),e.Plugin.NodeFX=n},"3.17.2",{requires:["node-pluginhost","anim-base"]});
/*
YUI 3.17.2 (build 9c3c78e)
Copyright 2014 Yahoo! Inc. All rights reserved.
Licensed under the BSD License.
http://yuilibrary.com/license/
*/

YUI.add("anim-scroll",function(e,t){var n=Number;e.Anim.behaviors.scroll={set:function(e,t,r,i,s,o,u){var a=e._node,f=[u(s,n(r[0]),n(i[0])-n(r[0]),o),u(s,n(r[1]),n(i[1])-n(r[1]),o)];f[0]&&a.set("scrollLeft",f[0]),f[1]&&a.set("scrollTop",f[1])},get:function(e){var t=e._node;return[t.get("scrollLeft"),t.get("scrollTop")]}}},"3.17.2",{requires:["anim-base"]});
