"use strict";

$(document).ready(function () {
  if ($('#coursesCreate').length > 0) {
    CourseInit();
  }

  function CourseInit() {
    var _this = this;

    // $('#ClassAction').submit(function (e) {
    //     submitfile.call(this, e);
    // });
    $('#CreateOne').on('click', function (e) {
      return CreateOneprompt.call(_this, e);
    });
    $('#Create').on('click', function (e) {
      return Createprompt.call(_this, e);
    }); //Modal To Create a New Course

    function CreateOneprompt(e) {
      var results = $('.results');
      var html = '<label for="oneSection"><b>Section</b></label>' + '<input type="text" placeholder="12345" name="oneSection" >' + '<label for="oneName"><b>Class Name</b></label>' + '<input type="text" placeholder="CIS 5" name="oneName" >' + '<label for="oneProfessor"><b>Professor</b></label>' + '<input type="text" placeholder="Enter Professor Name" name="oneProfessor" >' + '<div class="errors"></div>' + '<input id="CreateOneCourse" type="submit" value="Create"/>';
      results.html(html);
      results = $('.adminphase2');
      results.html("");
      results = $('.adminphase2pages');
      results.html("");
      results = $('.filters');
      results.html("");
      $('#CreateOneCourse').on('click', function (e) {
        CreateOneCourse.call(this, e);
      });
    }

    function CreateOneCourse(e) {
      e.preventDefault();
      var form = $('#ClassAction');
      var error = $('.errors', form);
      var errors = [];
      var data = $(form).serializeArray();
      var map = {}; //get data

      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      errors = verifyForm(form, {
        oneProfessor: {
          regex: regex['name'],
          msg: "Must be a real name"
        },
        oneSection: {
          regex: regex['section'],
          msg: "Must be a course section using only 5 numbers"
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
              messageModal(d.data.msg, "Register", false, "", true);
            } else {
              error.append("<p>" + d.data.error + "</p>");
              error.slideDown(250);
            }
          }
        });
      }
    }

    function Createprompt(e) {
      var _this2 = this;

      var results = $('.results');
      html = '<p>Enter a .csv <a href="https://drive.google.com/file/d/1plKnd1YyTAYtuvcvWWhIv-PnRgV_MTCk/view?usp=sharing">file as</a> <br>Sectios&emsp;Class &ensp;Professor<br>12345 &ensp;CSC 5 &emsp;David</p>' + '<input type="file" id="filecheck" name="file" accept="application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"/>';
      results.html(html);
      $('#filecheck').on('change', function (e) {
        return CreateCourse.call(_this2, e);
      });
    }

    function CreateCourse(e) {
      var form = $('#ClassAction');
      var formData = new FormData(form[0]);
      $.ajax({
        type: 'POST',
        dataType: 'json',
        url: CORE_URL + $(form).attr('action'),
        data: formData,
        //form data
        contentType: false,
        processData: false,
        success: function success(d) {
          //Table options
          var th = ['Edit', 'Section', 'Class Name', 'Professor'];
          var index = d.data.index;
          var checkbox = [['edit', 'section', index[0]]];
          var info = [['text', 'section', 'section', index[0]], ['text', 'classname', 'class', index[1]], ['text', 'professor', 'professor', index[2]]];
          var submitvals = {
            id: 'CreateFromtable',
            value: "Upload to Database"
          };
          var display = 'adminphase2';
          max = 50;
          filters = 3;

          if (d.success) {
            results = $('.' + display);
            results.fadeIn();
            createtable('FileTable', th, checkbox, info, d.data.info, submitvals, display, max, filters);
            var checkboxmains = ["edit"];
            var checkboxothers = [];
            var pclass = ["section", "classname", 'professor']; //Only one checkbox is possible at a time

            onlyonecheckbox();
            ptoanyinput(checkboxmains, checkboxothers, pclass, "text");
            $('#CreateFromtable').on('click', function (e) {
              submitfile.call(this, e);
            });
          } else {
            messageModal(d.data.error, "Upload to Database", false, "", true);
          }
        }
      });
    }

    function submitfile(e) {
      e.preventDefault(); //Function Variables

      var form = $('#ClassAction');
      var error = $('.errors', form);
      var data = $(form).serializeArray();
      var map = {}; //get data

      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      $.ajax({
        type: 'POST',
        url: CORE_URL + $(form).attr('action'),
        dataType: 'json',
        data: map,
        success: function success(d) {
          if (d.success) {
            if (d.data.errors) {
              messageModal(d.data.errors, "Error Uploading To The Database", false, "", true);
            } else {
              messageModal(d.data.msg, "Upload to Database", false, "", true);
            }
          } else {
            error.append("<p>" + d.data.error + "</p>");
            error.slideDown(250);
          }
        }
      });
    }
  }
});