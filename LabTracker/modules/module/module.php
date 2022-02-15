<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 2/3/2018 23:51
	 */
	abstract class module{
		protected $moduleName;
		protected $model;
		public $app;

		public function __construct( App $app, $name ){
			$this->moduleName = $name;
			$this->app = $app;
			$this->model = $app->loadModel( $this->moduleName );
		}

		public function loadView( $view, $data = array() ){
			$this->app->loadView( $this->moduleName, $view, $data );
		}

		/**
		 * used to fetch one record from the database
		 * @param array $options all options can vary
		 * @return mixed
		 */
//		public abstract function fetchOne( $options = array() );
		/**
		 * Used to fetch multiple records from the database
		 * @param array $options all options can vary
		 * @return mixed
		 */
		public abstract function fetch( $options = array() );

		/**
		 * Used to fetch a single record from the database
		 * @param array $options all options can vary
		 * @return mixed
		 */
		public abstract function fetchOne( $options = array() );
	}