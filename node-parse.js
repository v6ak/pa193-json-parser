var sprintf=require("sprintf-js").sprintf;
var fs = require('fs');
fs.readFile('/dev/stdin', function (err, data) {
  if (err) {
    throw err; 
  }
  var data = JSON.parse(data.toString());
  switch(typeof data){
    case 'string':
      process.stdout.write(data);
      break;
    case 'number':
      process.stdout.write(sprintf("%.5f", data));
      break;
    default:
      process.stdout.write("Unknown: "+typeof data);
  }
});
