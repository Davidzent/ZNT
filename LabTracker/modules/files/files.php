<?php
    /**
     * Copyright (C) Michael Risher - All Rights Reserved
     * Unauthorized copying of this file, via any medium is strictly prohibited
     * Proprietary and confidential
     * Written by Michael Risher <rishermichael@gmail.com>, 8/8/21 2:05 AM
     */

    class files extends module {

        /**
         * @inheritDoc
         */
        public function fetch( $options = array() ) {
            // TODO: Implement fetch() method.
        }

        /**
         * @inheritDoc
         */
        public function fetchOne( $options = array() ) {
            // TODO: Implement fetchOne() method.
        }

        public function getDataAsCsv( $data ){
			header("Content-type: text/csv");
			header("Content-Disposition: attachment; filename=file.csv");
			header("Pragma: no-cache");
			header("Expires: 0");

			$s = '';
			foreach ( $data[ 'headers' ] as $item ) {
				$s .= '"' . $item . '",';
			}
			echo trim( $s, ',') . "\n";

			foreach ( $data[ 'data' ] as $key => $item ) {
				$s ='';
				foreach ( $item as $x) {
					$s .= '"' . $x . '",';
				}
				echo trim( $s, ',') . "\n";
			}
		}

		public function test(){
			header("Content-type: text/csv");
			header("Content-Disposition: attachment; filename=file.csv");
			header("Pragma: no-cache");
			header("Expires: 0");

			echo "id,test\n";
			echo "1,true\n";
		}
    }