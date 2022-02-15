<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 2/3/2018 23:09
	 */
	class Debug {

		/**
		 * debug var to screen
		 * @param $arr
		 */
		public static function println( $arr ){
			echo '<pre>';
			print_r( $arr );
			echo '</pre>';
		}

		public static function adminPrintln( $arr ){
			if( Core::getRole() >= users::ADMIN ){
				self::println( $arr );
			}
		}

		public static function simpleJson( $str, $forceReturn = false ) {
			if( $forceReturn ){
				return "<pre>".json_encode( $str, JSON_PRETTY_PRINT ) . "</pre>";
			} else {
				echo '<pre>';
				echo json_encode( $str, JSON_PRETTY_PRINT );
				echo '</pre>';
			}
		}

		public static function json( $str ) {
			echo '<pre id="debug-ace-json">';
			echo json_encode( $str, JSON_PRETTY_PRINT );
			echo '</pre>';
			Core::queueScript( 'assets/js/ace.js' );
			Core::includeScripts();
			echo '<script>var a = ace.edit( "debug-ace-json" );a.session.setMode( "ace/mode/json" );a.session.setUseWrapMode(true);</script>';
		}

		public static function getDetails(){
			return debug_backtrace();
		}

		public static function logError( $string ){
			$debug = debug_backtrace()[1];
			//todo check that this works on linux servers
			$file = str_replace( CORE_ROOT, '', $debug['file'] );
			$output =  $string . '  [' . $file . ':' . $debug['line'] .  ' ' . $debug['class'] . $debug['type'] . $debug['function'] . '()]';
			echo $output;
			error_log( $output );
		}

		/**
		 * gets the json error from the php json error codes
		 * @param $code
		 * @return string
		 */
		public static function getJsonError( $code ){
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

		public static function callStack(){
			$details = self::getDetails();
			$str = '';
			foreach ( $details as $i => $item ) {
				$str .= $i+1 . ') ';
				$str .= trim( CORE_DIR, '/' ) . explode( trim( CORE_DIR, '/' ), $item['file'] )[1] . ' ';
				$str .= ( isset( $item['class'] ) ? $item['class'] . '->' : '' );
				$str .= $item['function'] . '():' . $item['line'];

				$str .= "\n";
			}
			return $str;
		}
	}