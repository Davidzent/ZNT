"use strict";

/**
 * Copyright (C) Michael Risher - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Michael Risher <rishermichael@gmail.com>, 6/17/2021 00:00
 */
$(document).ready(function () {
  if ($('#usersKiosk').length > 0) {
    kioskInit();
  }

  if ($('#usersLogin').length > 0) {
    loginInit();
  }

  if ($('#usersChangePassword').length > 0) {
    changePassInit();
  }

  if ($('#usersAdmin').length > 0) {
    AdminInit();
  }

  function kioskInit() {
    var _this = this;

    $('#LogIn').submit(function (e) {
      kioskIdSubmit.call(this, e);
    });
    $('#AddCourseForm').submit(function (e) {
      AddClassAction.call(this, id);
    });
    $('#RegisterStudent').submit(function (e) {
      registerAction.call(this, id);
    });
    $('#cancel ').on('click', function (e) {
      return kioskCancel.call(_this, e);
    });
    $('#Register').on('click', function (e) {
      return KioskRegisterModal.call(_this, e);
    });
    $('#AddCourse').on('click', function (e) {
      return UserAddCourseModal.call(_this, e);
    });
    $(document).on("contextmenu", function (e) {
      blockRightClick.call(this, e);
    }); // $(document).on( "keypress", function(e){ blockKeyboard.call( this, e) } );
    // window.onbeforeunload = function (e) {
    //     alert(1)
    // }

    function kioskIdSubmit(e) {
      e.preventDefault();
      var form = $(this);
      var error = $('.errors', form);
      var errors = [];
      var data = $(form).serializeArray();
      var map = {}; //hide/lock input

      $('.sidInput .progress-line', form).fadeIn(100);
      $('.sidInput input', form).prop('disabled', true); //$('.Register .log',form).
      //get data

      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      var phase = map.phase;

      if (phase == 1) {
        map.sid = $('.phase1 [name=sid]').val();
      } else if (phase == 2) {
        map.sid = $('.phase2 [name=sid]').val();
      }

      var hasError = false;

      if (phase == 1) {
        errors = verifyForm(form, {
          sid: {
            regex: regex['sid'],
            msg: "Must be a student id using only numbers"
          }
        });
      } else {
        //todo check for possible errors here
        errors = false;
      }

      if (errors) {
        displayErrors(form, error, errors);
        error.slideDown();
        $('input[name=sid]').effect('shake', 'slow');
        $('.sidInput .progress-line', form).fadeOut(100);
        $('.sidInput input', form).prop('disabled', false);
      } else {
        error.slideUp();
        displayErrors(form, error, errors);
        $.ajax({
          type: 'POST',
          url: CORE_URL + $(form).attr('action'),
          dataType: 'json',
          data: map,
          success: function success(d) {
            if (d.success) {
              //get the phase
              var list = $('.courses');

              if (d.data.phase === 1) {
                var courses = d.data.courses;

                for (var i = 0; i < courses.length; i++) {
                  var s = courses[i].section + "  " + courses[i].name + ' (' + courses[i].professor.ucwords() + ') ' + courses[i].time.toLocaleLowerCase();
                  list.append('<div class="course"><label><input type="radio" name="course" value="' + courses[i].id + '">' + s + '</label></div>');
                } //persist sid


                $('.sid[type=hidden]').val(map.sid);
                $('input[name=phase]').val(2);
                $('.phase1').fadeOut();
                $('.phase2').fadeIn();
              } else if (d.data.phase === 2) {
                list.html('');
                $('input[name=phase]').val(1);
                $('.sid[type=hidden]').val('');
                $('.phase2').fadeOut();
                $('.phase1').fadeIn(); // $( '.result' ).html( d.data.msg).fadeIn(250);
                // setTimeout( () => {$( '.result' ).html( '' ).fadeOut(250)}, 5000 );

                $('.result').html(d.data.msg);
                ajaxAction(d.data);
                $('form').fadeOut(100, function () {
                  return $('.result').fadeIn(250);
                });
                setTimeout(function () {
                  $('form').fadeIn(100, function () {
                    $('.result').fadeOut(250, function () {
                      return $('.result').empty();
                    });
                  });
                }, 5000);
              } //unlock/hide/clear sid


              $('.sidInput .progress-line', form).fadeOut(100);
              $('.sidInput input', form).prop('disabled', false);
              $('.sidInput input', form).val('');
            } else {
              log(d.data.lel);
              log(d.data.lol);
              error.append("<p>" + d.data.error + "</p>");
              error.slideDown(250);
              $('.sidInput .progress-line', form).fadeOut(100);
              $('.sidInput input', form).prop('disabled', false);
              $('.sidInput input', form).val('');
            }
          }
        });
      }
    } //Register a new student


    function registerAction(id) {
      //do some action.
      //get the form in the modal
      var form = $('.modal[data-id=' + id + '] form');
      var data = $(form).serializeArray();
      var map = {};
      var errors = [];
      var error = $('.errors', form);
      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify
      //            const phase = map.PhaseRegister;
      //gonna be similar to the way kioskIdSubmit does the form action with ajax
      //            if (phase == 1) {

      errors = verifyForm(form, {
        StudentID: {
          regex: regex['sid'],
          msg: "Must be a student id using only 7 numbers"
        },
        Fname: {
          regex: regex['name'],
          msg: "Must be a real name"
        },
        Lname: {
          regex: regex['name'],
          msg: "Must be a real name"
        },
        section: {
          regex: regex['section'],
          msg: "Must be a course section using only 5 numbers"
        }
      }); //            } else if (phase == 2) {
      //                errors = verifyForm(form, {
      //                    Professor: {
      //                        regex: regex['name'],
      //                        msg: "Must be a real name"
      //                    }
      //                });
      //            }

      if (errors) {
        displayErrors(form, error, errors);
        error.slideDown();
      } else {
        displayErrors(form, error, errors);
        $.ajax({
          type: 'POST',
          dataType: 'json',
          url: CORE_URL + $(form).attr('action'),
          //i reccomend making a function in students outside the kiosk in users to make it easier to trace
          data: map,
          //form data
          success: function success(d) {
            if (d.success) {
              //                            if (d.data.phase === 1) {
              $('.StudentID[type=hidden]').val(map.StudentID);
              $('.Fname[type=hidden]').val(map.Fname);
              $('.Lname[type=hidden]').val(map.Lname);
              $('input[name=PhaseRegister]').val(2);
              $('.PhaseRegister1').fadeOut();
              $('.PhaseRegister2').fadeIn(); //                            } else if (d.data.phase === 2) {

              closeModalId(id);
              messageModal(d.data.msg, "Register", false, "", true); //                            } else {
              //        //                            log('phase stuff broke');
              //                            }
            } else {
              error.append("<p>" + d.data.error + "</p>");
              error.slideDown(250);
            }
          }
        });
      }
    } //Modal for the student to be register


    function KioskRegisterModal(e) {
      var _this2 = this;

      e.preventDefault();
      var options = {
        title: "Register",
        shadowClose: false,
        noExit: false,
        focus: true,
        wide: false,
        footer: true,
        buttons: [{
          value: "Register",
          onclick: function onclick(id) {
            if (registerAction.call(_this2, id)) {
              closeModalId(id);
            }

            ;
          }
        }]
      };
      var html = '<form id = "RegisterStudent" method="post" action = "users/kiosk">' + //                '<input type="hidden" name="PhaseRegister" value="1" />' +
      //                '<div class="PhaseRegister1">' +
      '<label for="Fname"><b>First Name</b></label>' + '<input type="text" placeholder="Enter First Name" name="Fname" >' + '<label for="Lname"><b>Last Name</b></label>' + '<input type="text" placeholder="Enter Last Name" name="Lname" >' + '<label for="StudentID"><b>Student ID</b></label>' + '<input type="text" placeholder="1234567" name="StudentID" >' + '<label for="section"><b>Class Section</b></label>' + '<input type="text" placeholder="12345" name="section" >' + //                '</div>' +
      //                '<div class="PhaseRegister2 none">' +
      //                '<label for="Name"><b>Class Name</b></label>' +
      //                '<input type="text" placeholder="CIS 5" name="Name" >' +
      //                '<label for="Professor"><b>Professor</b></label>' +
      //                '<input type="text" placeholder="Enter Professor Name" name="Professor" >' +
      //                '</div>' +
      '<div class="errors"></div>' + '</form>';
      var modaltest = createModal(options);
      setModalContent(modaltest, html);
      displayModal(modaltest, 1);
    }

    function AddClassAction(id) {
      //get the form in the modal
      var form = $('.modal[data-id=' + id + '] form');
      var data = $(form).serializeArray();
      var map = {};
      var errors = [];
      var error = $('.errors', form);
      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      errors = verifyForm(form, {
        Section: {
          regex: regex['section'],
          msg: "Must be a section using only 5 numbers"
        },
        StudentID: {
          regex: regex['sid'],
          msg: "Must be a student id using only 7 numbers"
        }
      });

      if (errors) {
        displayErrors(form, error, errors);
        error.slideDown();
      } else {
        displayErrors(form, error, errors);
        $.ajax({
          type: 'POST',
          dataType: 'json',
          url: CORE_URL + $(form).attr('action'),
          data: map,
          //form data
          success: function success(d) {
            if (d.success) {
              $('.PhaseAdd1').fadeOut();
              $('.PhaseAdd2').fadeIn();
              closeModalId(id);
              messageModal(d.data.msg, "Add Course", false, "", true);
            } else {
              log(d.data.lel);
              error.append("<p>" + d.data.error + "</p>");
              error.slideDown(250);
            }
          }
        });
      }
    } //Modal To Create a New Course


    function UserAddCourseModal(e) {
      var _this3 = this;

      e.preventDefault();
      var options = {
        title: "Add Course",
        shadowClose: false,
        noExit: false,
        focus: true,
        wide: false,
        footer: true,
        buttons: [{
          value: "Add Course",
          onclick: function onclick(id) {
            if (AddClassAction.call(_this3, id)) {
              closeModalId(id);
            }

            ;
          }
        }]
      };
      var html = '<form id="AddCourseForm" method="post" action = "users/kiosk">' + '<label for="Section"><b>Section</b></label>' + '<input type="text" placeholder="12345" name="Section" >' + '<label for="StudentID"><b>Student ID</b></label>' + '<input type="text" placeholder="1234567" name="StudentID" >' + '<div class="errors"></div>' + '</form>';
      var modaltest = createModal(options);
      setModalContent(modaltest, html);
      displayModal(modaltest, 1);
    }

    function kioskCancel(e) {
      e.preventDefault();
      $('input[name=phase]').val(1);
      $('.sid[type=hidden]').val('');
      $('.phase2').fadeOut();
      $('.phase1').fadeIn();
      $('.courses').html('');
    }

    function blockRightClick(e) {
      e.preventDefault();
    }

    function blockKeyboard(e) {
      log(e.key, e.keyCode);

      if (e.key === "F12") {
        alert(1);
      }
    }
  }

  function loginInit() {
    $("#login").submit(function (e) {
      loginSubmit.call(this, e);
    });

    function loginSubmit(e) {
      e.preventDefault();
      var form = $(this);
      var error = $('.errors', form);
      var errors = [];
      var data = $(form).serializeArray();
      var map = {};
      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      var hasError = false;
      errors = verifyForm(form, {
        email: {
          regex: regex['email'],
          msg: "Email must be a valid email"
        },
        password: {
          msg: "Password must not be blank"
        }
      });

      if (errors) {
        displayErrors(form, error, errors);
        error.slideDown();
      } else {
        error.slideUp();
        displayErrors(form, error, errors);
        map.password = sha512(map.password);
        $.ajax({
          type: 'POST',
          url: CORE_URL + $(form).attr('action'),
          dataType: 'json',
          data: map,
          success: function success(d) {
            if (d.success) {
              var ref = getQueryString()['ref'];

              if (ref) {
                location.href = CORE_URL + ref.ltrim('/');
              } else if (isset(d.data.action)) {
                ajaxAction(d.data);
              }
            } else {
              error.append(d.data.error);
              error.slideDown();
            }
          }
        });
      }
    }
  }

  function changePassInit() {
    passwordHints();
    $('#changePass').submit(function (e) {
      changeSubmit.call(this, e);
    });

    function changeSubmit(e) {
      e.preventDefault();
      var form = $(this);
      var error = $('.errors', form);
      var errors = [];
      var data = $(form).serializeArray();
      var map = {};
      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      var hasError = false;
      errors = verifyForm(form, {
        password: {
          msg: "Password must not be blank"
        },
        newPassword: {
          regex: regex['password'],
          msg: "New password must be 10 characters long, contain at least 1 number, uppercase and lowercase letter, and symbol",
          confirm: true,
          confirmMsg: "New passwords must match"
        }
      });

      if (errors) {
        displayErrors(form, error, errors);
        error.slideDown();
      } else {
        error.slideUp();
        displayErrors(form, error, errors);
        map.password = sha512(map.password);
        map.newPassword = sha512(map.newPassword);
        $.ajax({
          type: 'POST',
          url: CORE_URL + $(form).attr('action'),
          dataType: 'json',
          data: map,
          success: function success(d) {
            if (d.success) {
              var modal = createModal({
                title: 'Message',
                buttons: [{
                  value: 'Ok',
                  focus: true,
                  onclick: function onclick() {
                    ajaxAction(d.data);
                  }
                }]
              });
              setModalContent(modal, d.data.msg);
              displayModal(modal);
            } else {
              error.append(d.data.error);
              error.slideDown();
            }
          }
        });
      }
    }
  }

  function AdminInit() {
    //edit roles button
    $(document).on('click', '#EditUserTable input.edit-roles', function (e) {
      editRoles.call(this, e);
    });
    $(document).on('click', '#EditUserTable #EditUserCreate', function (e) {
      createUser.call(this);
    });
    $(document).on('click', '#VASLogAll', function () {
      $('[name^=LogoutStudents]').prop('checked', true);
      $('#VASSubmit').click();
    });
    $('#AdminAction').submit(function (e) {
      AdminAction.call(this, e);
    });

    function AdminAction(e) {
      e.preventDefault();
      var submitter = e.originalEvent.submitter.id;
      var form = $(this);

      if (submitter == 'Verify' || submitter == 'VerifySubmit') {
        $('input[name=option]').val(1);

        if (submitter == 'Verify') {
          $('input[name=phase]').val(1);
        } else {
          $('input[name=phase]').val(2);
        }

        AdminVerify(form);
      } else if (submitter == 'VAS' || submitter == 'VASSubmit') {
        $('input[name=option]').val(2);

        if (submitter == 'VAS') {
          $('input[name=phase]').val(1);
        } else {
          $('input[name=phase]').val(2);
        }

        AdminVAS(form);
      } else if (submitter == 'EditReports' || submitter == 'EditReportsSubmit') {
        $('input[name=option]').val(3);

        if (submitter == 'EditReports') {
          $('input[name=phase]').val(1);
        } else {
          $('input[name=phase]').val(2);
        }

        AdminEditReports(form);
      } else if (submitter == 'EditSection' || submitter == 'EditSectionSubmit') {
        $('input[name=option]').val(4);

        if (submitter == 'EditSection') {
          $('input[name=phase]').val(1);
        } else {
          $('input[name=phase]').val(2);
        }

        AdminEditClasses(form);
      } else if (submitter == 'EditIncompleteReports' || submitter == 'EditIncompleteReportsSubmit') {
        $('input[name=option]').val(5);

        if (submitter == 'EditIncompleteReports') {
          $('input[name=phase]').val(1);
        } else {
          $('input[name=phase]').val(2);
        }

        AdminEditReports(form);
      } else if (submitter == 'EditStudents' || submitter == 'EditStudentsSubmit') {
        $('input[name=option]').val(6);

        if (submitter == 'EditStudents') {
          $('input[name=phase]').val(1);
        } else {
          $('input[name=phase]').val(2);
        }

        AdminEditStudents(form);
      } else if (submitter == 'EditStudentClasses' || submitter == 'EditStudentClassesSubmit') {
        $('input[name=option]').val(7);

        if (submitter == 'EditStudentClasses') {
          $('input[name=phase]').val(1);
        } else {
          $('input[name=phase]').val(2);
        }

        AdminEditStudentClasses(form);
      } else if (submitter === 'EditUsers' || submitter === 'EditUserSubmit') {
        $('input[name=option]').val(8);

        if (submitter === 'EditUsers') {
          $('input[name=phase]').val(1);
        } else {
          $('input[name=phase]').val(2);
        }

        AdminEditUsers(form);
      } else if (submitter === 'EditTerm' || submitter === 'EditTermSubmit') {
        $('input[name=option]').val(9);

        if (submitter === 'EditTerm') {
          $('input[name=phase]').val(1);
        } else {
          $('input[name=phase]').val(2);
        }

        AdminEditTerm(form);
      } else {
        $('input[name=option]').val(10);
        log('10');
        messageModal("You Should not see this", "Admin Options", false, "", true);
      }
    }

    function AdminEditTerm(form) {
      var error = $('.errors', form);
      var data = $(form).serializeArray();
      var map = {}; //get data

      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      var phase = map.phase;
      error.slideDown();
      error.empty();
      $.ajax({
        type: 'POST',
        url: CORE_URL + $(form).attr('action'),
        dataType: 'json',
        data: map,
        success: function success(d) {
          if (d.success) {
            //Table options
            var th = ['Edit48595', 'Term', 'Start Date', 'End Date'];
            var checkbox = [['edit', 'EditTerms', 'term']];
            var info = [['term', 'term'], ['date', 'startdate', 'startdate', 'startDate'], ['date', 'endtdate', 'endtdate', 'endDate']];
            var submitvals = {
              length: 1,
              0: {
                id: 'EditTermSubmit',
                value: "Edit Terms",
                type: 'submit'
              }
            };
            var display = 'adminphase2';
            max = 50;
            filters = 2;
            $('input[name=phase]').val(2);
            createtable('EditTermsTable', th, checkbox, info, d.data.terms, submitvals, display, max, filters);
            var checkboxmains = ["edit"];
            var checkboxothers = [];
            var pclass = ["startdate", "endtdate"]; //Only one checkbox is possible at a time

            onlyonecheckbox();
            ptoanyinput(checkboxmains, checkboxothers, pclass, 'date');

            if (phase == 2) {
              if (d.data.errors) {
                messageModal(d.data.errors, "Edit Students", false, "", true);
              } else {
                messageModal(d.data.msg, "Edit Students", false, "", true);
              }
            } else {//log("phase stuff broke");
            }
          } else {
            var results = $('.adminphase2');
            log(d.data.lel);
            log(d.data.lol);
            results.empty();
            error.html(d.data.error);
          }
        }
      });
    }

    function AdminEditStudentClasses(form) {
      var error = $('.errors', form);
      var data = $(form).serializeArray();
      var map = {}; //get data

      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      var phase = map.phase;
      error.slideDown();
      error.empty();
      $.ajax({
        type: 'POST',
        url: CORE_URL + $(form).attr('action'),
        dataType: 'json',
        data: map,
        success: function success(d) {
          if (d.success) {
            //Table options
            var th = ['Edit', 'Remove', 'Section', 'Student ID', 'First Name', 'Last Name', 'Term'];
            var checkbox = [['edit', 'EditStudentClass', 'id'], ['remove', 'RemoveStudentClass', 'id']];
            var info = [['text', 'small section', 'section', 'section'], ['text', 'small studentid', 'sid', 'sid'], ['fname', 'firstname'], ['lname', 'lastname'], ['term', 'term']];
            var submitvals = {
              length: 1,
              0: {
                id: 'EditStudentClassesSubmit',
                value: "Edit Students Classes",
                type: 'submit'
              }
            };
            var display = 'adminphase2';
            max = 50;
            filters = 4;
            $('input[name=phase]').val(2);
            createtable('EditStudentsClassesTable', th, checkbox, info, d.data.studentclasses, submitvals, display, max, filters);
            var checkboxmains = ["edit"];
            var checkboxothers = ["remove"];
            var pclass = ["small section", "small studentid"]; //Only one checkbox is possible at a time

            onlyonecheckbox();
            ptoanyinput(checkboxmains, checkboxothers, pclass, 'text');

            if (phase == 2) {
              if (d.data.errors) {
                messageModal(d.data.errors, "Edit Students", false, "", true);
              } else {
                messageModal(d.data.msg, "Edit Students", false, "", true);
              }
            } else {//log("phase stuff broke");
            }
          } else {
            var results = $('.adminphase2');
            log(d.data.lel);
            log(d.data.lol);
            results.empty();
            error.html(d.data.error);
          }
        }
      });
    }

    function editRoles(e) {
      var tr = $(this).closest('tr');
      var id = $('input.edit', tr).val();
      log(tr);
      var modal = {
        title: "Edit Roles",
        buttons: [{
          value: 'Save',
          onclick: function onclick(modalId) {
            return saveRoles(modalId, id);
          }
        }, {
          value: 'Cancel'
        }]
      };
      modal = createModal(modal);
      setModalContentAjax(modal, CORE_URL + 'users/editRole/' + id);
      displayModal(modal);

      function saveRoles(modalId, id) {
        var modal = $('.modal[data-id=' + modalId + ']');
        var data = {};
        $('.modalContent input', modal).each(function (i, elem) {
          data[$(elem).attr('name')] = {
            id: $(elem).val(),
            checked: $(elem).prop('checked') ? 1 : 0
          };
        });
        var ret = false;
        $.ajax({
          type: 'POST',
          url: CORE_URL + 'users/editRole/' + id,
          dataType: 'json',
          data: data,
          async: false,
          //TODO make a work around its not great to do this but im to lazy/tired atm
          success: function success(d) {
            if (d.success) {
              ret = true;
            } else {
              errorModal("An unknown error occurred. Try to refresh the page");
              ret = false;
            }
          }
        });
        return ret;
      }
    }

    function createUser() {
      var modal = {
        title: "Create User",
        shadowClose: false,
        buttons: [{
          value: 'Create',
          onclick: function onclick(id) {
            //do stuff
            submitUser(id); //update table
          }
        }, {
          value: 'Cancel'
        }]
      };
      modal = createModal(modal);
      setModalContentAjax(modal, CORE_URL + 'users/create/');
      displayModal(modal);

      function submitUser(id) {
        var modal = $('.modal[data-id=' + id + ']');
        var form = $('form', modal);
        var error = $('.errors', form);
        var data = $(form).serializeArray();
        var map = {};
        jQuery.each(data, function (i, field) {
          map[field.name] = field.value;
        }); //get form data for verify

        var hasError = false;
        var errors = verifyForm(form, {
          email: {
            regex: regex['email'],
            msg: "Email must be a valid email"
          },
          fname: {
            strlen: {
              min: 1
            },
            msg: "First name must be at least 1 character"
          },
          lname: {
            strlen: {
              min: 1
            },
            msg: "Last name must be at least 1 character"
          },
          password: {
            strlen: {
              min: 5
            },
            msg: "Password must be at least 5 characters"
          }
        }); //add the all checkboxes form simplification

        $('input[type=checkbox]', modal).each(function (i, elem) {
          map[$(elem).attr('name')] = $(elem).prop('checked') ? 1 : 0;
        });

        if (errors) {
          displayErrors(form, error, errors);
          error.slideDown();
        } else {
          error.slideUp();
          displayErrors(form, error, errors);
          map.password = sha512(map.password);
          var ret = false;
          $.ajax({
            type: 'POST',
            url: CORE_URL + 'users/create/',
            dataType: 'json',
            data: map,
            success: function success(d) {
              if (d.success) {
                $('input[name=phase]').val(1);
                AdminEditUsers($('form#AdminAction'));
                closeModal(modal);
              } else {
                errorModal(d.error);
                ret = false;
              }
            }
          });
          return ret;
        }
      }
    }

    function AdminEditUsers(form) {
      var error = $('.errors', form);
      var errors = [];
      var data = $(form).serializeArray();
      var map = {}; //get data

      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      var phase = map.phase;
      error.slideDown();
      error.empty();
      $.ajax({
        type: 'POST',
        url: CORE_URL + $(form).attr('action'),
        dataType: 'json',
        data: map,
        success: function success(d) {
          //todo get this to work later
          var data = d.data.items;
          var th = ['Edit', 'Remove', 'Email', 'First Name', 'Last Name', 'Roles'];
          var checkbox = [['edit', 'edit', 'id'], ['remove', 'remove', 'id']];
          var info = [['text', 'email', 'email', 'email'], ['text', 'firstname', 'fname', 'fname'], ['text', 'lastname', 'lname', 'lname'], ['button', 'minor edit-roles', 'roles', 'Edit Roles']];
          var submitvals = {
            length: 2,
            0: {
              id: 'EditUserSubmit',
              value: 'Save Edits',
              type: 'submit'
            },
            1: {
              id: 'EditUserCreate',
              value: 'Create User',
              type: 'button'
            }
          };
          var display = 'adminphase2';
          max = 50;
          filters = 2;

          if (d.success) {
            $('input[name=phase]').val(2);
            createtable('EditUserTable', th, checkbox, info, data, submitvals, display, max, filters); // let users=d.data.items;
            // let results = $('.adminphase2');
            // results.fadeIn();
            // let html="<table id='EditUserTable' class='dataTable'><thead><tr>" +
            //     "<th>Edit</th><th>Remove</th><th>Email</th><th>First Name</th><th>Last Name</th><th>Roles</th></tr></thead><tbody>";
            // let i = 0;
            // for( const item in users ){
            //     html+="<tr><td class='center'>"+
            //         "<input id = '"+i+"' class='edit' name = 'edit["+i+"]' value='"+users[item].id+"' type='checkbox' /></td>"+
            //         "<td td class='center'>"+
            //         "<input id = '"+i+"' class='remove' name = 'remove["+i+"]' value='"+users[item].id+"' type='checkbox' /></td>"+
            //         "<td class = 'wide vcenter'><input class='email"+i+"' name = 'email["+i+"]' value='"+users[item].email+"' type='hidden' />"+
            //         "<p class = 'email"+i+"'>"+users[item].email+"</p></td>"+
            //         "<td class = 'wide vcenter'><input class='fname"+i+"' name = 'fname["+i+"]' value='"+users[item].fname+"' type='hidden' />"+
            //         "<p class = 'fname"+i+"'>"+users[item].fname+"</p></td>"+
            //         "<td class = 'wide vcenter'><input class='lname"+i+"' name = 'lname["+i+"]' value='"+users[item].lname+"' type='hidden' />"+
            //         "<p class = 'lname"+i+"'>"+users[item].lname+"</p></td>" +
            //         "<td><input type='button'  class='edit-roles minor' value='Edit Roles' /></td>"
            //         "</tr>"
            //     ;
            //     i++
            // }
            // html+='</tbody><tfoot><td colspan="8"><input id="EditUserSubmit" type = "submit" value = "Save Edits"/>' +
            //     '<input id="EditUserCreate" type = "button" value = "Create User"/></td></tfoot></table>'
            // results.html(html);

            var checkboxmains = ["edit"];
            var checkboxothers = ["remove"];
            var pclass = ["email", "firstname", "lastname"];
            onlyonecheckbox();
            ptoanyinput(checkboxmains, checkboxothers, pclass, 'text'); // addfilter("EditUserTable","Email");
            // filtertable("EditUserTable");

            if (phase === '2') {
              if (d.data.errors) {
                messageModal(d.data.errors, "Edit Staff", false, "", true);
              } else {
                messageModal(d.data.msg, "Edit Staff", false, "", true);
              }
            }
          } else {}
        }
      });
    }

    function AdminEditStudents(form) {
      var error = $('.errors', form);
      var data = $(form).serializeArray();
      var map = {}; //get data

      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      var phase = map.phase;
      error.slideDown();
      error.empty();
      $.ajax({
        type: 'POST',
        url: CORE_URL + $(form).attr('action'),
        dataType: 'json',
        data: map,
        success: function success(d) {
          if (d.success) {
            //Table options
            var th = ['Edit', 'Remove', 'Student ID', 'First Name', 'Last Name'];
            var checkbox = [['edit', 'EditStudent', 'id'], ['remove', 'RemoveStudent', 'id']];
            var info = [['text', 'small studentid', 'id', 'id'], ['text', 'small firstname', 'fname', 'fname'], ['text', 'small lastname', 'lname', 'lname']];
            var submitvals = {
              length: 1,
              0: {
                id: 'EditStudentsSubmit',
                value: "Edit Students",
                type: 'submit'
              }
            };
            var display = 'adminphase2';
            max = 50;
            filters = 3;
            $('input[name=phase]').val(2);
            createtable('EditStudentsTable', th, checkbox, info, d.data.students, submitvals, display, max, filters);
            var checkboxmains = ["edit"];
            var checkboxothers = ["remove"];
            var pclass = ["small studentid", "small firstname", "small lastname"]; //Only one checkbox is possible at a time

            onlyonecheckbox();
            ptoanyinput(checkboxmains, checkboxothers, pclass, 'text');

            if (phase == 2) {
              if (d.data.errors) {
                messageModal(d.data.errors, "Edit Students", false, "", true);
              } else {
                messageModal(d.data.msg, "Edit Students", false, "", true);
              }
            }
          } else {
            var results = $('.adminphase2');
            log(d.data.lel);
            log(d.data.lol);
            results.empty();
            error.html(d.data.error);
          }
        }
      });
    }

    function AdminEditClasses(form) {
      var error = $('.errors', form);
      var data = $(form).serializeArray();
      var map = {}; //get data

      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      var phase = map.phase;
      error.slideDown();
      error.empty();
      $.ajax({
        type: 'POST',
        url: CORE_URL + $(form).attr('action'),
        dataType: 'json',
        data: map,
        success: function success(d) {
          if (d.success) {
            //Table options
            var th = ['Edit', 'Remove', 'Section', 'Name', 'Professor', 'Students Enrolled', 'Completed Records', 'Incomplete Records', 'term'];
            var checkbox = [['edit', 'EditSection', 'section'], ['remove', 'RemoveSection', 'section']];
            var info = [['text', 'small section', 'section', 'section'], ['text', 'small name', 'name', 'name'], ['text', 'small professor', 'professor', 'professor'], ['countStudents', 'studentsenrolled'], ['countComplete', 'completedrecords'], ['countIncomplete', 'incompleterecords'], ['term', 'term']];
            var submitvals = {
              length: 1,
              0: {
                id: 'EditSectionSubmit',
                value: "Edit Classes",
                type: 'submit'
              }
            };
            var display = 'adminphase2';
            max = 2;
            filters = 5;
            $('input[name=phase]').val(2);
            createtable('EditSectionTable', th, checkbox, info, d.data.classes, submitvals, display, max, filters);
            var checkboxmains = ["edit"];
            var checkboxothers = ["remove"];
            var pclass = ["small section", "small name", "small professor"]; //Only one checkbox is possible at a time

            onlyonecheckbox();
            ptoanyinput(checkboxmains, checkboxothers, pclass, 'text');

            if (phase == 2) {
              if (d.data.errors) {
                messageModal(d.data.errors, "Edit Sections", false, "", true);
              } else {
                messageModal(d.data.msg, "Edit Sections", false, "", true);
              }
            }
          } else {
            var results = $('.adminphase2');
            log(d.data.lel);
            log(d.data.lol);
            results.empty();
            error.html(d.data.error);
          }
        }
      });
    }

    function AdminEditReports(form) {
      //Function Variables
      var error = $('.errors', form);
      var data = $(form).serializeArray();
      var map = {}; //get data

      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      var phase = map.phase;
      error.slideDown();
      error.empty();
      $.ajax({
        type: 'POST',
        url: CORE_URL + $(form).attr('action'),
        dataType: 'json',
        data: map,
        success: function success(d) {
          if (d.success) {
            //Table options
            var th = ['Edit', 'Remove', 'Section', 'Student ID', 'First Name', 'Last Name', 'Time in', 'Time Out', 'Term'];
            var checkbox = [['edit', 'EditReportsStudents', 'id'], ['remove', 'RemoveStudents', 'id']];
            var info = [['text', 'small section', 'section', 'section'], ['sid', 'studentid'], ['fname', 'firstname'], ['lname', 'lastname'], ['datetime-local-convert', 'timein', 'timein', 'timein'], ['datetime-local-convert', 'timeout', 'timeout', 'timeout'], ['term', 'term']];
            var submitvals = {
              length: 1,
              0: {
                id: d.data.id,
                value: "Edit Selected Records",
                type: 'submit'
              }
            };
            var display = 'adminphase2';
            max = 50;
            filters = 5;
            $('input[name=phase]').val(2);
            createtable('EditReportsTable', th, checkbox, info, d.data.students, submitvals, display, max, filters);
            var checkboxmains = ["edit"];
            var checkboxothers = ["remove"];
            var pclass = ["timein", "timeout"]; //Only one checkbox is possible at a time

            onlyonecheckbox();
            ptoanyinput(checkboxmains, checkboxothers, pclass, "datetime-local");
            pclass = ["small section"];
            ptoanyinput(checkboxmains, checkboxothers, pclass, "text");

            if (phase == 2) {
              if (d.data.errors) {
                messageModal(d.data.errors, "Edit Reports", false, "", true);
              } else {
                messageModal(d.data.msg, "Edit Reports", false, "", true);
              }
            }
          } else {
            var results = $('.adminphase2');
            results.empty();
            error.html(d.data.error);
          }
        }
      });
    }

    function AdminVAS(form) {
      var error = $('.errors', form);
      var errors = [];
      var data = $(form).serializeArray();
      var map = {}; //get data

      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      var phase = map.phase;
      error.slideDown();
      error.empty();
      $.ajax({
        type: 'POST',
        url: CORE_URL + $(form).attr('action'),
        dataType: 'json',
        data: map,
        success: function success(d) {
          if (d.success) {
            //Table options
            var th = ['Logout', 'Section', 'Student ID', 'First Name', 'Last Name', 'Time'];
            var checkbox = [['logout', 'LogoutStudents', 'id']];
            var info = [['section', 'section'], ['sid', 'studentid'], ['fname', 'firstname'], ['lname', 'lastname'], ['time', 'time']];
            var submitvals = {
              length: 1,
              0: {
                id: 'VASSubmit',
                value: "Logout Students",
                type: 'submit'
              }
            };
            var extra = {
              value: 'Logout All Students',
              id: 'VASLogAll'
            };
            var display = 'adminphase2';
            max = 50;
            filters = 4;
            $('input[name=phase]').val(2);
            createtable('EditReportsTable', th, checkbox, info, d.data.students, submitvals, display, max, filters, extra);

            if (phase == 2) {
              messageModal(d.data.msg, "Logging Out Students", false, "", true);
            }
          } else {
            var results = $('.adminphase2');
            results.empty();
            error.html(d.data.error);
          }
        }
      });
    }

    function AdminVerify(form) {
      var error = $('.errors', form);
      var errors = [];
      var data = $(form).serializeArray();
      var map = {}; //get data

      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      var phase = map.phase;
      error.slideDown();
      error.empty();
      $.ajax({
        type: 'POST',
        url: CORE_URL + $(form).attr('action'),
        dataType: 'json',
        data: map,
        success: function success(d) {
          if (d.success) {
            //Table options
            var th = ['Verify', 'Section', 'Student ID', 'First Name', 'Last Name'];
            var checkbox = [['Verify', 'ValidatedStudents', 'id']];
            var info = [['section', 'section'], ['sid', 'studentid'], ['fname', 'firstname'], ['lname', 'lastname']];
            var submitvals = {
              length: 1,
              0: {
                id: 'VerifySubmit',
                value: "Verify Students",
                type: 'submit'
              }
            };
            var display = 'adminphase2';
            max = 50;
            filters = 4;
            $('input[name=phase]').val(2);
            createtable('EditReportsTable', th, checkbox, info, d.data.students, submitvals, display, max, filters);

            if (phase == 2) {
              messageModal(d.data.msg, "Verify Students", false, "", true);
            } else {//log("phase stuff broke");
            }
          } else {
            var results = $('.adminphase2');
            results.empty();
            error.append(d.data.error);
          }
        }
      });
    }

    function filtertable(tableid) {
      $("#filter").on('keyup', function () {
        var table = document.getElementById(tableid);
        var index = document.getElementById("filtertag").value;
        var tr;
        var td;
        var txtValue;
        var keywords = $(this).val().toUpperCase();
        var x = 0;
        tr = table.getElementsByTagName("tr");

        if (index != null) {
          for (var i = 1; i < tr.length - 1; i++) {
            td = tr[i].getElementsByTagName("td")[index];

            if (td) {
              txtValue = td.textContent || td.innerText;

              if (txtValue.toUpperCase().indexOf(keywords) > -1) {
                tr[i].style.display = "";

                if (x % 2 == 1) {
                  tr[i].style.backgroundColor = "rgb(255, 120, 120)";
                  x++;
                } else {
                  tr[i].style.backgroundColor = "rgba(24, 26, 27, 0)";
                  x++;
                }
              } else {
                tr[i].style.display = "none";
              }
            }
          }
        }
      });
      $("#filtertag").change(function () {
        var table = document.getElementById(tableid);
        var index = $(this).val();
        var tr;
        var td;
        var txtValue;
        var keywords = document.getElementById("filter").value = "";
        var x = 0;
        tr = table.getElementsByTagName("tr");

        if (index != null) {
          for (var i = 1; i < tr.length - 1; i++) {
            td = tr[i].getElementsByTagName("td")[index];

            if (td) {
              txtValue = td.textContent || td.innerText;

              if (txtValue.toUpperCase().indexOf(keywords) > -1) {
                tr[i].style.display = "";

                if (x % 2 == 1) {
                  tr[i].style.backgroundColor = "rgb(255, 120, 120)";
                  x++;
                } else {
                  tr[i].style.backgroundColor = "rgba(24, 26, 27, 0)";
                  x++;
                }
              } else {
                tr[i].style.display = "none";
              }
            }
          }
        }
      });
    }
  }
});

function passwordHints() {
  $('input[type=password].hints').on({
    'focus': function focus() {
      var div = $(this).closest('div');
      $('.passwordPopover', div).fadeIn();
    },
    'blur': function blur() {
      var div = $(this).closest('div');
      $('.passwordPopover', div).fadeOut();
    },
    'keyup': function keyup() {
      var val = $(this).val();
      var div = $(this).closest('div');
      var details = $('.passwordPopover', div);

      if (val.length >= 10) {
        $('.length', details).html('<i class="fa green fa-check" aria-hidden="true"></i>');
      } else {
        $('.length', details).html('<i class="fa red fa-times" aria-hidden="true"></i>');
      }

      if (/[A-Z]/.test(val)) {
        $('.upper', details).html('<i class="fa green fa-check" aria-hidden="true"></i>');
      } else {
        $('.upper', details).html('<i class="fa red fa-times" aria-hidden="true"></i>');
      }

      if (/[a-z]/.test(val)) {
        $('.lower', details).html('<i class="fa green fa-check" aria-hidden="true"></i>');
      } else {
        $('.lower', details).html('<i class="fa red fa-times" aria-hidden="true"></i>');
      }

      if (/\d/.test(val)) {
        $('.number', details).html('<i class="fa green fa-check" aria-hidden="true"></i>');
      } else {
        $('.number', details).html('<i class="fa red fa-times" aria-hidden="true"></i>');
      }

      if (/[&"'(\-_)=~#{[|`\\^@\]}^$*???%,;:!?./?+]/.test(val)) {
        $('.symbol', details).html('<i class="fa green fa-check" aria-hidden="true"></i>');
      } else {
        $('.symbol', details).html('<i class="fa red fa-times" aria-hidden="true"></i>');
      }
    }
  });
}