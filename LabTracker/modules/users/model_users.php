<?php
    /**
     * Copyright (C) Michael Risher - All Rights Reserved
     * Unauthorized copying of this file, via any medium is strictly prohibited
     * Proprietary and confidential
     * Written by Michael Risher <rishermichael@gmail.com>, 7/12/21 4:59 PM
     */

    class model_users extends model_module {

        public function getRoles( $userId = -1){
            $items = $this->get([
                'fields' => 'r.id, r.name, r.friendly',
                'table' => 'usersXroles as u inner join roles as r on u.roleId = r.id',
                'where' => 'u.userId=?',
                'params' => [ $userId ]
            ]);

            $out = [
                'ids' => '',
                'names' => '',
                'friendly' => []
            ];
            foreach ( $items as $item ) {
                $out['ids'] .= $item['id'] . '|';
                $out['names'] .= $item['name'] . '|';
                $out['friendly'][ $item['id'] ] = $item['friendly'];
            }
            $out['ids'] = rtrim( $out['ids'], "|" );
            $out['names'] = rtrim( $out['names'], "|" );

            return $out;
        }

        /**
         * insert a single role
         * @param int $userId
         * @param int $roleId
         * @return bool|int
         */
        public function addRole( $userId, $roleId ){
            return $this->insertOne( [
                'fields' => 'userId,roleId',
                'params' => [ $userId, $roleId ],
                'table' => 'usersXroles'
            ]);
        }

        /**
         * insert a single role
         * @param int $userId
         * @param int $roleId
         * @return bool|int
         */
        public function deleteRole( $userId, $roleId ){
            return $this->delete( [
                'where' => 'userId=? AND roleId=?',
                'params' => [ $userId, $roleId ],
                'table' => 'usersXroles'
            ]);
        }

        /**
         * delete a user and attached roles
         * @param int $id
         * @return bool
         */
        public function deleteUser( $id = -1 ){
            if( $id != -1 ){
                //remove roles
                $this->delete([
                    'table' => 'usersXroles',
                    'where' => 'userId=?',
                    'params' => [ $id ]
                ]);

                return $this->delete([
                    'id' => $id,
                ]);
            }
        }
    }