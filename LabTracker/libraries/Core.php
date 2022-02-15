<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 2/3/2018 22:58
	 */
	class Core {
		const LOWER_CASE = 1;
		const UPPER_CASE = 2;
		const NORMAL_CASE = 0;
		public static $uniqueIds = array();

		/**
		 * Makes a unique 42 character string from sha1
		 * @return string
		 */
		public static function uniqueId( $length = 40 ){
			do {
				$str = microtime( true ) . $_SERVER['REQUEST_TIME_FLOAT'] . $_SERVER['HTTP_HOST'];
				$str = sha1( $str );
				if ( $length <= 40 ) {
					$str = substr( $str, 0, $length );
				}
			} while( self::inArray( $str, self::$uniqueIds ) );
			array_push( self::$uniqueIds, $str );
			return $str;
		}

		/**
		 * creates a user friendly string with no I0Ol
		 * @param int $len length of the string to create
		 * @param int $case
		 * @return string
		 */
		public static function userFriendlyId( $len, $case = self::NORMAL_CASE ){
			$string = "abcdefghijkmnopqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ123456789";
			$size = strlen( $string ) - 1;
			$result = '';
			for( $i = 0; $i < $len; $i++ ){
				$result .= $string[rand(0, $size )];
			}
			switch( $case ){
				case self::UPPER_CASE:
					$result = strtoupper( $result );
					break;
				case self::LOWER_CASE:
					$result = strtolower( $result );
					break;
			}
			return $result;
		}

		/**
		 * Give data to turn into a json response
		 * @deprecated moved to class AJAX
		 * @param $data
		 * @param bool|true $status
		 * @param $msg
		 * @return string
		 */
		public static function ajaxResponse( $data, $status = true, $msg = null ){
			$o['success'] = $status;
			if( empty( $data ) ){
				$data = [];
			}
			$o['data'] = $data;
			if( isset( $msg ) && $status ){
				$o['data']['msg'] = $msg;
			} else if( isset( $msg ) && !$status ){
				$o['data']['error'] = $msg;
			}
			if( IS_AJAX ){
				if( json_encode( $o ) ){
					return json_encode( $o );
				} else{
					return self::jsonError( json_last_error() );
				}
			} else {
				echo json_encode( $o );
			}
		}

		/**
		 * @param $data
		 * @param bool|true $status
		 * @param null $msg
		 * @return string
		 */
		public static function response( $data, $status = true, $msg = null ){
			$o['success'] = $status;
			$o['data'] = $data;
			if( isset( $msg ) ){
				$o['msg'] = $msg;
			}

			if( json_encode( $o ) ){
				return json_encode( $o );
			} else{
				return self::jsonError( json_last_error() );
			}
		}

		/**
		 * gives the json error in plain text
		 * @param $code
		 * @return string
		 */
		public static function jsonError( $code ){
			switch ( $code ) {
				case JSON_ERROR_NONE:
					return ' - No errors';
					break;
				case JSON_ERROR_DEPTH:
					return ' - Maximum stack depth exceeded';
					break;
				case JSON_ERROR_STATE_MISMATCH:
					return ' - Underflow or the modes mismatch';
					break;
				case JSON_ERROR_CTRL_CHAR:
					return ' - Unexpected control character found';
					break;
				case JSON_ERROR_SYNTAX:
					return ' - Syntax error, malformed JSON';
					break;
				case JSON_ERROR_UTF8:
					return ' - Malformed UTF-8 characters, possibly incorrectly encoded';
					break;
				default:
					return ' - Unknown error';
					break;
			}
		}

		/**
		 * get options and insert default options if none are set in the arguments
		 * @param array $keys the default values
		 * @param array $arguments the passed in arguments
		 * @return array
		 */
		static function getOptions($keys, $arguments) {
			// the $keys are name=>value. they are the final defaults.
			// $arguments always override things.
			// (this + is called the 'array union operator')

			$options = ( is_array($arguments) ? $arguments : array() ) + $keys;

			return $options;
		}

		/**
		 * Queue a script up to be included
		 * @param string $url
		 */
		public static function queueScript( $url ) {
			if ( file_exists( CORE_PATH . $url ) ) {
				$GLOBALS['scriptQueue'][$url] = CORE_URL . $url . '?' . filemtime( $url );
			} elseif( substr( $url, 0, 4 ) === "http" ) {
				$GLOBALS['scriptQueue'][$url] = $url;
			}
		}

		/**
		 * include the scripts in the page
		 */
		public static function includeScripts() {
			foreach ( $GLOBALS['scriptQueue'] as $url ) {
				?>
				<script src="<?= $url; ?>" type="text/javascript"></script><?php
			}
			$GLOBALS['scriptQueue'] = array();
		}

		/**
		 * Queue a style up to be included
		 * @param String $url
		 */
		public static function queueStyle( $url ) {
			if ( file_exists( CORE_PATH . $url ) ) {
				$GLOBALS['styleQueue'][$url] = CORE_URL . $url . '?' . filemtime( $url );
			} elseif( substr( $url, 0, 4 ) === "http" ) {
				$GLOBALS['styleQueue'][$url] = $url;
			}
		}

		/**
		 * include the scripts in the page
		 */
		public static function includeStyles() {
			foreach ( $GLOBALS['styleQueue'] as $url ) {
				?>
				<link rel="stylesheet" href="<?= $url; ?>" type="text/css" media="all" /><?php
			}
			$GLOBALS['styleQueue'] = array();
		}

		/**
		 * Redirect the user to a different page
		 * @param string $page page to redirect to
		 */
		public static function phpRedirect( $page ){
			header('Location: ' . CORE_URL . $page );
		}

		/**
		 * creates a timer dom element that will counter down
		 * @param int $time time in seconds
		 * @return string
		 */
		public static function createTimer( $time ){
			return "<span class='timer' data-time='$time'>$time</span>";
		}

		/**
		 * returns the users ip
		 * @return mixed
		 */
		public static function getIp(){
			return $_SERVER['REMOTE_ADDR'];
		}

		/**
		 * converts an assoc array to a flat indexed array
		 * @param array $array
		 * @return array
		 */
		public static function assocToFlat( $array ){
			$temp = array();
			foreach ( $array as $item ) {
				array_push( $temp, $item );
			}
			return $temp;
		}

		/**
		 * improved array_search that returns true or false if it was found in the array
		 * @param mixed $needle what we are looking for
		 * @param array $array array in which we are looking through
		 * @return bool true if found false if not
		 */
		public static function inArray( $needle, $array ){
			if( array_search( $needle, $array ) !== false ){
				return true;
			} else {
				return false;
			}
		}

		/**
		 * gets the date in a assoc array
		 * @return array
		 */
		public static function getDate(){
			$date = date('n/j/Y');
			$date = explode( "/" , $date );
			return array( 'month' => $date[0], 'day' => $date[1], 'year' => $date[2] );
		}

		public static function copyright(){
			$y = date("Y");
			echo "Copyright <i class='far fa-copyright'></i> 2021-$y, Michael Risher & David Guijosa Infante. All rights reserved.";
		}

		/**
		 * pluralize nouns ie add an s when int is greater than 1
		 * @param $int
		 * @param $str
		 * @param string $plural
		 * @return string
		 */
		public static function pluralize( $int, $str, $plural = 's' ){
			if( $int != 1 ){
				return $str . $plural;
			}
			return $str;
		}

		/**
		 * turns mysql datetime to a html5 input format
		 * @deprecated
		 * @param $d
		 * @param bool|false $return
		 * @return bool|string
		 */
		public static function datetimeFormat( $d, $return = false ){
			if( $return ){
				return date( 'Y-m-d\TH:i', strtotime( $d ) );
			}
			echo date( 'Y-m-d\TH:i', strtotime( $d ) );
		}

		/**
		 * Converts the machine time to human readable time
		 * @deprecated
		 * @param $date
		 * @param string $format
		 * @return bool|string
		 */
		public static function humanDate( $date, $format = "n/j/y g:i A" ){
			return date( $format, strtotime( $date ) );
		}

		/**
		 * get a role without having to check if the user is logged in.
		 * only used to not have to test if set all the time
		 * @return string
		 */
		public static function getRoles(){
			if( isset( $_SESSION['session'] ) && isset( $_SESSION['session']['roles'] ) ){
				return $_SESSION['session']['roles'];
			} else {
				return '';
			}
		}

        /**
         * Check if the session has the role in it
         * @param int $role id of the role. get from users consts
         * @return bool
         */
        public static function hasRole( $role ){
            if( isset( $_SESSION['session'] ) && isset( $_SESSION['session']['roles'] ) ){
                $pos = strpos( $_SESSION['session']['roles'], (string) $role);
                return ( ( $pos === false ) ? ( false ) : ( true ) );
            } else {
                return false;
            }
        }

		/**
		 * get a user without having to check if the user is logged in.
		 * only used to not have to test if set all the time
		 * @return int
		 */
		public static function getUser(){
			if( isset( $_SESSION['session'] ) && isset( $_SESSION['session']['id'] ) ){
				return $_SESSION['session']['id'];
			} else {
				return 0;
			}
		}

		public static function getFileContentsUtf8( $filename ) {
			$content = file_get_contents( $filename );
			return mb_convert_encoding( $content, 'UTF-8', mb_detect_encoding( $content, 'UTF-8, ISO-8859-1', true ) );
		}

		/**
		 * converts \n and \r to html escaped newline characters.
		 * @param $str
		 * @return mixed
		 */
		public static function mewLineToEntity( $str ){
			$str = preg_replace( '/\r?\n/', '&#013;', $str );
			return $str;
		}

		/**
		 * flattens an array of
		 * 0 : [
		 * 		item : 1
		 * ]
		 * to [1] if using the item as the index
		 * @param array $array array that is to be flattened
		 * @param mixed $index the column in the assoc array that is wanted to be looked at
		 * @return array the flat 1d array
		 */
		public static function flattenArray( $array, $index ){
			$result = [];
			foreach ( $array as $item ) {
				array_push( $result, $item[$index] );
			}
			return $result;
		}

		/**
		 * checks if the text is empty "0" are considered not empty
		 * null, false, "", [] are considered empty
		 * @param $s
		 * @return bool
		 */
		public static function textEmpty( $s ){
			if( !isset( $s ) ) { //not set empty
				return true;
			}
			if( is_array( $s ) ){
				if( count( $s ) == 0 )
					return true;
				return false;
			}
			if( strlen( $s ) == 0 ){
				return true;
			}
		}

        /**
         * Is optional return. check if item is set else returns optional value
         * @param mixed $item item to check if is set
         * @param null $opt return if not set
         * @return mixed|null
         */
		public static function opt( $item, $opt = null ){
		    if( isset( $item ) ){
		        return $item;
            } else {
		        return $opt;
            }
        }
	}