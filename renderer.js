// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.

const serialport = require('serialport');

const portParser = () => {
        serialport.list().then(portList => {
                portList.forEach(dataPort => {
                        if(dataPort.manufacturer == "Arduino (www.arduino.cc)") {
				startListener(dataPort.path);
                        	return;
			}
                });
        });
}

portParser();

const startListener = (portStr) => {
	const port = new serialport(portStr, { baudRate: 9600 });

	port.on('open', () => {
		console.log('pog the communication gateway between pi->arduino is now open.');
	});

	port.on('data', data => {
		console.log('pog new data from the other side of the coms gateway: ' + data);
	});

	const servo = () => {
        	console.log('hi');
        	port.write('servo-run');
	};

	document.getElementById('controller').onclick = servo;
}
