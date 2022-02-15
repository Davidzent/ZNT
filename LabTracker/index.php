<?php
	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 2/3/2018 22:58
	 */
	require_once 'config.php';
	date_default_timezone_set('America/Los_Angeles');
	//ini_set( 'zlib.output_compression', 1 );

	/*
    echo CORE_DIR . '<BR>';
    echo CORE_PATH . '<BR>';
    echo CORE_ROOT . '<BR>';
    echo CORE_URL . '<BR>';
    die();*/
	//error logging
	function __error($errno, $errstr, $errfile = null, $errline = null) {
		switch ($errno) {
			case E_ERROR:
				$type = logs::PHP_ERROR;
				break;
			case E_WARNING:
				$type = logs::PHP_WARNING;
				break;
			case E_DEPRECATED:
				$type = logs::PHP_DEPRECATED;
				break;
			default:
				$type = logs::PHP_NOTICE;
				break;
		}

		$GLOBALS['app']->logs->error( $errstr, $type, $errfile . ':' . $errline);
		return MODE == 'local' ? false : true;
	}

	function __fatalError() {
		$error = error_get_last();

		if ($error !== null) {
			__error($error['type'], $error['message'], $error['file'], $error['line']);
		}
	}

	function autoload( $className ) {
		$lib = CORE_PATH . 'libraries/' . $className . '.php';
		if( IS_AJAX ){ //to make the Core work on the classes and cert pages
			if( MODE == 'local' ) {
				$lib = $_SERVER['DOCUMENT_ROOT'] . '/' . CORE_DIR . 'libraries/' . $className . '.php';
			} elseif( MODE == 'live' || MODE == 'staging' ){
				$lib = CORE_ROOT . CORE_DIR . 'libraries/' . $className . '.php';
			}
		}
		if( file_exists( $lib ) ){
			require_once( $lib );
		}
	}

	//autoloader
	spl_autoload_register( 'autoload' );

	//enable error loging
	set_error_handler('__error');
	register_shutdown_function( '__fatalError' );

	//clean get for injections
	$_GET = Security::sanitize( $_GET );
	//get the url from the get
	$url = ( isset( $_GET['url'] ) ? $_GET['url'] : null );

	//start sessions
	session_start();

	//allow cross domain
	header('Access-Control-Allow-Origin: *');

	$uri = array( 'module' => null, 'function' => null, 'params' => null );

	$url = trim( $url, '/' );
	$tempUri = preg_split( '/\//', $url, 3 );
	$uri['module'] = ( !empty( $tempUri[0] ) ? $tempUri[0] : '' );
	$uri['function'] = ( isset( $tempUri[1] ) ? $tempUri[1] : '' );
	if ( isset( $tempUri[2] ) ) {
		$tempVar = preg_split( '/\//', $tempUri[2] );
		if ( !empty( $tempVar ) ) {
			//todo it might be better to always have it as an array
			$uri['params'] = ( count( $tempVar ) == 1 ? $tempUri[2] : $tempVar );
		}
	}

	//some globals for page loading
	$scriptQueue = array();
	$styleQueue = array();

	//load the Main class
	//require the app and the default inherited module
    require_once( 'App.php' );
    require_once( 'modules/module/module.php' );
    require_once( 'modules/module/model_module.php' );
    $main = new App();
//    die();
    $GLOBALS['app'] = &$main;

	$main->loadModule( 'users' );
	$main->loadModule( 'logs' );

	//check for expired session
//	$main->users->checkExpiredSession();

	//set cookie with the core_url
	setcookie( "url", CORE_URL, time() + 3600 * 24 * ( 2 ), '/' );

	//might want this in the future
	// Enable Cross Domain requests.
	//header('Access-Control-Allow-Origin: *');


	//invoke the request
	$main->loadModule( $uri['module'] );
	if( strpos( $uri['function'], '__' ) === 0 ){
		$main->throwError( 404 );
	} else if ( isset( $uri['params'] ) ) {
		if ( method_exists( $main->{$uri['module']}, $uri['function'] ) ) {
			$reflection = new ReflectionMethod( $main->{$uri['module']}, $uri['function'] );
			if( $reflection->isPublic() ){
				$response = $main->{$uri['module']}->{$uri['function']}( $uri['params'] );
			} else {
				$main->throwError( 404 );
			}
		} else {
			$main->throwError( 404 );
		}
	} else {
		if ( method_exists( $main->{$uri['module']}, $uri['function'] ) ) {
			$reflection = new ReflectionMethod( $main->{$uri['module']}, $uri['function'] );
			if( $reflection->isPublic() ) {
				$response = $main->{$uri['module']}->{$uri['function']}();
			} else {
				$main->throwError( 404 );
			}
		} else {
			$main->throwError( 404 );
		}
	}
	//set last location
	$_SESSION['lastPage'] = ( isset( $_SERVER['HTTP_REFERER'] ) ? $_SERVER['HTTP_REFERER'] : '' );
//	echo $_SESSION['lastPage'];

//	echo Core::uniqueId();



	/*
	$GLOBALS['main']->loadModule( $uri['module'] );
	if ( isset( $uri['params'] ) ) {
		if( method_exists( $GLOBALS['main']->$uri['module'], $uri['function'] ) ){
			$response = $GLOBALS['main']->$uri['module']->{$uri['function']}($uri['params']);
		} else {
			Core::errorPage( 404 );
		}
	} else{
		if( method_exists( $GLOBALS['main']->$uri['module'], $uri['function'] ) ) {
			$response = $GLOBALS['main']->$uri['module']->{$uri['function']}();
		} else {
			Core::errorPage( 404 );
		}
	}
*/
