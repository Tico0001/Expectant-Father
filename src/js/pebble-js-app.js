Pebble.addEventListener('ready', function(e) 
	{
		console.log('PebbleKit JS ready!');
	}
);

Pebble.addEventListener('showConfiguration', function(e) 
	{
		var url = 'https://rawgit.com/Tico0001/Expectant-Father/master/config/index.html';
		console.log('Showing configuration page: ' + url);
		Pebble.openURL(url);
	}
);

var sendSuccess = function(e) 
{
    console.log("send Success, e: " + JSON.stringify(e));
    //console.log(
    //    'Successfully delivered message with transactionId=' +
    //    e.data.transactionId);
};

var sendFailure = function(e) 
{
    console.log("send Failure, e: " + JSON.stringify(e));
    console.log('Unable to deliver message with transactionId=' + e.data.transactionId);
	console.log('Error is: ' + e.data.error);
};

Pebble.addEventListener('webviewclosed', function(e)
	{
		var config_data = JSON.parse(decodeURIComponent(e.response));
		console.log('Configuration page returned: ' + JSON.stringify(config_data));
		
		// Prepare AppMessage payload
		var dict = {
			'KEY_WIFE_NAME': config_data['wife_name'],
			'KEY_BABY_NAME': config_data['baby_name'],
			'KEY_CONCEP_DATE': config_data['concep_date']
		};
		
		// Send to watchapp
		Pebble.sendAppMessage(dict, sendSuccess, sendFailure);
	}
);