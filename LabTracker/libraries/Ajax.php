<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 7/28/2020 13:13
	 */
	class Ajax {

		/**
		 * Echos a successful ajax request
		 * @param array|null $data the data to return to the client
		 * @param string $msg the message to give to the client this can be blank and included in the data
		 */
		public static function successResponse( $data = null, $msg = '' ){
			echo self::response( $data, true, $msg );
		}

		/**
		 * Echos a error ajax request
		 * @param string $msg
		 */
		public static function errorResponse( $msg = '' ){
			echo self::response( null, false, $msg );
		}


        /***
         * returns a json encoded string
         * @param $data
         * @param $status
         * @param string $msg
         * @return false|string
         */
		public static function response( $data, $status, $msg = '', $dataType = 'json' ){
			$o['success'] = $status;
			if( !empty( $dataType ) )
				$o['dataType'] = $dataType;
			if( empty( $data ) ){
				$data = [];
			}
			$o['data'] = $data;
			if( isset( $msg ) && $status ){
				$o['data']['msg'] = $msg;
			} else if( isset( $msg ) && !$status ){
				$o['data']['error'] = $msg;
			}
			if( json_encode( $o ) ){
				return json_encode( $o );
			} else{
				return self::jsonError( json_last_error() );
			}
		}

		public static function action( $type, $data ){
		    $r = [];
		    $r['action'] = $type;
		    $r = array_merge( $r, $data );
		    return $r;
        }
	}