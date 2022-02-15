<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 2/4/2018 18:50
	 * @property courses|null courses
	 * @property create|null create
	 * @property files|null files
	 * @property logs|null logs
	 * @property pages|null pages
	 * @property students|null students
	 * @property users|null users
	 */
	class App {
		private $vars;
		private $modules;

		/**
		 * declare the fields and start a connection to the database
		 */
		public function __construct() {
			$this->vars = array();
			$this->modules = array();
			$this->lastError = '';

			$connection = null;
			try {
				$driver = new mysqli_driver();
				$driver->report_mode = MYSQLI_REPORT_STRICT;
				$connection = new mysqli( DB_IP, DB_USER, DB_PASS, DB_DB );
				if ( $connection->connect_errno > 0 ) {
					http_response_code( 500 );
					$this->loadPage( 'fatal' );
				}
				$driver->report_mode = MYSQLI_REPORT_OFF;
			} catch(Exception $e ){
				restore_error_handler();
				http_response_code(500);
				if( IS_AJAX ){
					echo Core::ajaxResponse(['shutdown' => true ], false, "We are currently experiencing problems with the site. We apologize for the inconvenience and are working on fixing it as soon as we can.");
				} else {
					$this->loadPage( 'fatal' );
				}
				die();
			}
			if( SHUTDOWN && Core::getRole() < 5){
				if( IS_AJAX ){
					echo Core::ajaxResponse(['shutdown' => true ], false, "We are currently experiencing problems with the site. We apologize for the inconvenience and are working on fixing it as soon as we can.");
				} else {
					$this->loadPage( 'fatal' );
				}
				die();
			}
			$this->db = $connection;
			$this->dbHelper = new DbHelper( $this );
		}

        /**
         * magic destruction that closes the db connection
         */
		public function __destruct() {
			if ( $this->db !== null ) {
				$this->db->close();
			}
		}

		/**
		 * part of the "magic function"
		 * think of this
		 * $this->index = $value
		 * @param $index
		 * @param $value
		 */
		public function __set( $index, $value ) {
			$this->vars[$index] = $value;
		}

		/**
		 * gets what was set in the vars
		 * $value = this->index
		 * @param $index
		 * @return mixed
		 */
		public function __get( $index ) {
			if ( isset( $this->vars[$index] ) ) {
				return $this->vars[$index];
			} else {
				return null;
			}
		}

		/**
		 * load a module
		 * @param $name
		 */
		public function loadModule( $name ) {
			$temp = $this->__get( $name );
			if ( isset( $temp ) ) {
				return;
			}

			$class = $name;
			if ( file_exists( CORE_PATH . 'modules/' . $name . '/' . $name . '.php' ) ) {
				require_once( CORE_PATH . 'modules/' . $name . '/' . $name . '.php' );
			}

			$this->__set( $name, new $class( $this, $name ) );
		}

		/**
		 * load a modules
		 * @param $name
		 */
		public function loadModules( $name ) {
			$names = explode( ' ', $name );
			foreach ( $names as $n ) {
				$this->loadModule( $n );
			}

		}

		/**
		 * loads the models for the modules
		 * @param string $name name of the module
		 * @return mixed
		 */
		public function loadModel( $name ){
			$class = 'model_' . $name;
			if ( file_exists( CORE_PATH . 'modules/' . $name . '/' . $class . '.php' ) ) {
				require_once( CORE_PATH . 'modules/' . $name . '/' . $class . '.php' );
//				echo CORE_PATH . 'modules/' . $name . '/' . $class . '.php';
				return new $class( $this, $name );
			} else {
				//load the default model
				$class = 'model_module';
				require_once( CORE_PATH . 'modules/module/' . $class . '.php' );
				return new $class( $this, $name );
			}
			return null;
		}


        /**
         * loads a view html page in the module
         * @param $module string name of module
         * @param $view string name of the view to load minus the word view
         * @param array $data
         */
		public function loadView( $module, $view, $data = array() ){
			$file = CORE_PATH . 'modules/' . $module . '/view_' . $view . '.php';
			if( file_exists( $file ) ){
				$this->queueDefaults();
				if( MODE == 'local' ){
					if( file_exists( CORE_PATH . 'assets/js/' . $module . '.js' ) ) {
						Core::queueScript( 'assets/js/' . $module . '.js' );
					}
				} else {
					if( file_exists( CORE_PATH . 'assets/js/' . $module . '.min.js' ) ) {
						Core::queueScript( 'assets/js/' . $module . '.min.js' );
					}
				}
				if( file_exists( CORE_PATH . 'assets/css/' . $module . '.css' ) ) {
					Core::queueScript( 'assets/css/' . $module . '.css' );
				}
				$data['_id'] = $module . ucfirst( $view );
				require_once( $file );

			}
		}

		/**
		 * load a page from pages instead of a module view page,
		 * should be moved to pages module or call display but im lazy atm
		 * @param $page
		 * @param array $data
		 */
		public function loadPage( $page, $data = array() ){
			$file = CORE_PATH . 'pages/' . $page . '.php';
			if( file_exists( $file ) ){
				$this->queueDefaults();

				$data['_id'] = ucfirst( $page );
				require_once( $file );
			}
		}

		/**
		 * throws an error
		 * @param $code
		 */
		public function throwError( $code ) {
			$data['error'] = $code;
			header( 'HTTP/1.1 ' . $code );
			unset( $GLOBALS['style_queue'] );
			unset( $GLOBALS['script_queue'] );
			$this->queueDefaults();
			$data['error'] = $code;
			include( CORE_PATH . 'pages/error.php' );
			die;
		}

        /**
         * queue the default css and js required for all pages
         */
		public function queueDefaults(){
            Core::queueStyle( 'assets/css/reset.css' );
            Core::queueStyle( 'assets/css/ui.css' );
            Core::queueStyle( 'assets/css/jquery.datetimepicker.min.css' );
            Core::queueStyle( 'assets/css/font-awesome.css' );
            Core::queueStyle( 'assets/css/select2.css' );
            Core::queueScript( 'assets/js/core.js' );
            Core::queueScript( 'assets/js/jquery-ui.js' );
            Core::queueScript( 'assets/js/jquery.datetimepicker.full.min.js' );
            if( MODE === 'local' ){
				Core::queueScript( 'assets/js/library.js' );
				Core::queueScript( 'assets/js/ui.js' );
			} else {
				Core::queueScript( 'assets/js/library.min.js' );
				Core::queueScript( 'assets/js/ui.min.js' );
			}

        }
	}