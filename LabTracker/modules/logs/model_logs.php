<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 4/5/2018 12:01
	 */
	class model_logs extends model_module {

		/**
		 * truncates the log table
		 * @return bool true if ran false otherwise
		 */
		public function truncate(){
			$state = $this->app->db->prepare( "truncate logs" );
			return $state->execute();
		}

	}