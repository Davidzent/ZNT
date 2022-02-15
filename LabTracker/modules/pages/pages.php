<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 2/5/2018 10:11
	 */
	class pages extends module{

		public function fetch( $options = array() ) {
			return null;
		}

        public function fetchOne( $options = array() ) {
            return null;
        }

		public function display( $path ){
			if( is_array( $path ) ){
				$data['params'] = $path;
				$path = $path[0];
			} else{
				$data['params'] = $path;
			}

			//if the page exists load it with the params if there was any
			if ( file_exists( CORE_PATH . 'pages/' . $path .'.php' ) ) {
				$this->app->queueDefaults();
				include( CORE_PATH . 'pages/' . $path . '.php' );
			} else {
				//TODO this should use a database maybe
				$this->app->throwError( 404 );
			}
		}

		public function invert(){
			if( !isset( $_SESSION['dark'] ) ){
				$_SESSION['dark'] = true;
			} else {
				$_SESSION['dark'] = !$_SESSION['dark'];
			}
			if( isset( $_SERVER['HTTP_REFERER'] ) ){
				Core::phpRedirect( str_replace( CORE_URL, '', $_SERVER['HTTP_REFERER'] ) );
			}
		}

		public function lastPage(){
			if ( isset( $_SESSION['lastPage'] ) ) {
//				echo $_SESSION['lastPage'];
				header( "Location: " . $_SESSION['lastPage'] );
			} else {}
		}

	}