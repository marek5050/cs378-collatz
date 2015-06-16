#!/opt/local/bin/node

var util = require("util");

process.stdin.setEncoding('utf8');

/* http://stackoverflow.com/questions/1144783/replacing-all-occurrences-of-a-string-in-javascript */
function replaceAll(find, replace, str) {
  return str.replace(new RegExp(find, 'g'), replace);
}

var min = 1;
var max = 1000000;
var i=1;


// for(;i<102;i++){
//  // console.log(Math.floor(Math.random()*(max-min)+min) , Math.floor(max/i%max));
//  //console.log(Math.floor(Math.random()*i)+min +" "+Math.floor(Math.random()*i)+min);
// }
var val = 10;
var old = 0;

for(;i<100 && val <=max;i++){
 val = (i-1)*100 + 1;
 console.log(val + " " + (i*100));
}
//for(;i<500 && val <= max;i++){
//	val=Math.floor(Math.random()*10000)+min;
//	console.log(val + " " + (val+500));
//}
