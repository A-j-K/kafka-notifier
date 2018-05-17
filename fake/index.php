<?php

if(empty($_SERVER['PHP_AUTH_USER']) || empty($_SERVER['PHP_AUTH_PW'])) {
	header('WWW-Authenticate: Basic realm="My Realm"');
	header('HTTP/1.0 401 Unauthorized');
	header("Content-type: text/plain");
	echo "Access denied";
	exit(0);
}

$response = [
	'method' => $_SERVER['REQUEST_METHOD'],
	'result' => 'ok',
	'your-headers' => null,
	'your-body' => null
];

foreach(getallheaders() as $name => $value) {
	$response['your-headers'][$name] = $value;
}

$response['your-body'] = file_get_contents('php://input');

error_log("Recieved message\n");

header("Content-type: application/json");
echo json_encode($response, JSON_PRETTY_PRINT) . "\n\n";
exit(0);

