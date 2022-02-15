"use strict";

$(document).ready(function () {
  if ($('#reportsReport').length > 0) {
    ReportsInit();
  }

  function ReportsInit() {
    var _this = this;

    $(document).on('change', '#ReportsAction .daterangeterm', function (e) {
      SCDReports.call(this, e, 'daterange');
    });
    $(document).on('change', '#ReportsAction .TermReport', function (e) {
      TermReports.call(this, e);
    });
    $(document).on('keyup || change', '#ReportsAction .studentterm', function (e) {
      SCDReports.call(this, e, 'student');
    });
    $(document).on('keyup || change', '#ReportsAction .sectionterm', function (e) {
      SCDReports.call(this, e, 'section');
    });
    $(document).submit('#ReportsAction', function (e) {
      e.preventDefault();
    });
    $('#DateReport').on('click', function (e) {
      return promptDate.call(_this, e);
    });
    $('#StudentReport').on('click', function (e) {
      return promptStudent.call(_this, e, false);
    });
    $('#StudentReportDetails').on('click', function (e) {
      return promptStudent.call(_this, e, true);
    });
    $('#SectionReport').on('click', function (e) {
      return promptSection.call(_this, e);
    });
    $('#TermReport').on('click', function (e) {
      return promptTerm.call(_this, e);
    });

    function promptTerm() {
      var results = $('.adminphase2');
      results.html("");
      results = $('.filters');
      results.html("");
      var form = $('#ReportsAction');
      var error = $('.errors', form);
      error.html("");
      var map = {
        terms: 'term'
      };
      $.ajax({
        type: 'POST',
        dataType: 'json',
        url: CORE_URL + $(form).attr('action'),
        data: map,
        //form data
        success: function success(d) {
          if (d.success) {
            results = $('.result');
            var html = '<select class="TermReport" name="TermReport">' + '<option value="">Select a Term</option>';
            var terms = d.data.terms;

            for (var i = 0; i < terms.length; i++) {
              if (terms[i].current) {
                html += '<option selected value="' + terms[i].term + '">' + terms[i].term + '</option>';
              } else {
                html += '<option value="' + terms[i].term + '">' + terms[i].term + '</option>';
              }
            }

            html += '</select>';
            results.html(html);
            TermReports(null);
          } else {
            error.html(d.data.error);
          }
        }
      });
    }

    function promptSection() {
      var results = $('.adminphase2');
      results.html("");
      results = $('.filters');
      results.html("");
      var form = $('#ReportsAction');
      var error = $('.errors', form);
      error.html("");
      var map = {
        terms: 'term'
      };
      $.ajax({
        type: 'POST',
        dataType: 'json',
        url: CORE_URL + $(form).attr('action'),
        data: map,
        //form data
        success: function success(d) {
          if (d.success) {
            results = $('.result');
            var html = '<input class="sectionterm" placeholder="Section" type="text" name="section"/>' + '<select class="sectionterm" name="term">' + '<option value="">Select a Term</option>';
            var terms = d.data.terms;

            for (var i = 0; i < terms.length; i++) {
              if (terms[i].current) {
                html += '<option selected value="' + terms[i].term + '">' + terms[i].term + '</option>';
              } else {
                html += '<option value="' + terms[i].term + '">' + terms[i].term + '</option>';
              }
            }

            html += '</select>';
            results.html(html);
          } else {
            error.html(d.data.error);
          }
        }
      });
    }

    function promptStudent(e, details) {
      var results = $('.adminphase2');
      results.html("");
      results = $('.filters');
      results.html("");
      var form = $('#ReportsAction');
      var error = $('.errors', form);
      error.html("");
      var map = {
        terms: 'term'
      };
      $.ajax({
        type: 'POST',
        dataType: 'json',
        url: CORE_URL + $(form).attr('action'),
        data: map,
        //form data
        success: function success(d) {
          if (d.success) {
            results = $('.result');
            var html = '<input class="studentterm" placeholder="Student ID" type="text" name="studentid"/>';
            if (details) html += '<input type="hidden" name="studentDetails" value="1" />';
            html += '<select class="studentterm" name="term">' + '<option value="">Select a Term</option>';
            var terms = d.data.terms;

            for (var i = 0; i < terms.length; i++) {
              if (terms[i].current) {
                html += '<option selected value="' + terms[i].term + '">' + terms[i].term + '</option>';
              } else {
                html += '<option value="' + terms[i].term + '">' + terms[i].term + '</option>';
              }
            }

            html += '</select>';
            results.html(html);
          } else {
            error.html(d.data.error);
          }
        }
      });
    }

    function promptDate() {
      var results = $('.adminphase2');
      results.html("");
      results = $('.filters');
      results.html("");
      var form = $('#ReportsAction');
      var error = $('.errors', form);
      var map = {
        terms: 'term'
      };
      $.ajax({
        type: 'POST',
        dataType: 'json',
        url: CORE_URL + $(form).attr('action'),
        data: map,
        //form data
        success: function success(d) {
          if (d.success) {
            results = $('.result');
            var html = 'From: <input class="daterangeterm"  type="date" name="startdate"/>' + 'To: <input class="daterangeterm" type="date" name="enddate"/><br>' + '<select class="daterangeterm" name="term">' + '<option value="">Select a Term</option>';
            var terms = d.data.terms;

            for (var i = 0; i < terms.length; i++) {
              if (terms[i].current) {
                html += '<option selected value="' + terms[i].term + '">' + terms[i].term + '</option>';
              } else {
                html += '<option value="' + terms[i].term + '">' + terms[i].term + '</option>';
              }
            }

            html += '</select>';
            results.html(html);
          } else {
            error.html(d.data.error);
          }
        }
      });
    } //Student/Class/Date Total Hours for students (They basically are the same so I just made one for all of them)


    function SCDReports(e, option) {
      e.preventDefault();
      var max = -1;
      var filters = 0;
      var form = $('#ReportsAction');
      var error = $('.errors', form);
      var data = $(form).serializeArray();
      var map = {};
      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      var temp = false; //check the input

      if (option === 'student') {
        var details = $('input[name=studentDetails]', form).val();
        if (map.studentid.length === 7 && map.term) temp = true;
        if (details === '1') map.details = 1;else map.details = 0;
      } else if (option === 'daterange') {
        if (map.startdate && map.enddate && map.term) temp = true;
        filters = 3;
      } else if (option === 'section') {
        if (map.section.length === 5 && map.term) temp = true;
      }

      if (temp) {
        error.html("");
        $.ajax({
          type: 'POST',
          dataType: 'json',
          url: CORE_URL + $(form).attr('action'),
          data: map,
          //form data
          success: function success(d) {
            var display = 'adminphase2';

            if (d.dataType === 'raw') {
              $('.' + display).html(d.data.data).fadeIn();
            } else {
              //Table options
              var th = ['First Name', 'Last Name', 'Student ID', 'Class', 'Section', 'Cumulative Hours'];
              var reports = d.data.reports;
              var checkbox = [];
              var info = [['fname', 'firstname'], ['lname', 'lastname'], ['id', 'studentid'], ['name', 'name'], ['section', 'section'], ['hours', 'cumulativehours']];
              var submitvals = false;

              if (d.success) {
                results = $('.' + display);
                results.fadeIn();
                createtable('ReportsTable', th, checkbox, info, reports, submitvals, display, max, filters);
              } else {
                error.html(d.data.error);
              }
            }
          }
        });
      }
    }

    function TermReports(e) {
      if (e) {
        e.preventDefault();
      }

      var form = $('#ReportsAction');
      var error = $('.errors', form);
      var data = $(form).serializeArray();
      var map = {};
      jQuery.each(data, function (i, field) {
        map[field.name] = field.value;
      }); //get form data for verify

      error.html("");
      $.ajax({
        type: 'POST',
        dataType: 'json',
        url: CORE_URL + $(form).attr('action'),
        data: map,
        //form data
        success: function success(d) {
          //Table options
          var th = ['First Name', 'Last Name', 'Student ID', 'Class', 'Section', 'Cumulative Hours'];
          var reports = d.data.reports;
          var weeks = d.data.weeks;
          var checkbox = [];
          var info = [['fname', 'firstname'], ['lname', 'lastname'], ['id', 'studentid'], ['name', 'name'], ['section', 'section'], ['hours', 'cumulativehours']];

          for (var i = 0; i < weeks; i++) {
            th.push('Week ' + (i + 1));
            info.push(['week' + i, 'week' + (i + 1)]);
          }

          var submitvals = false;
          var display = 'adminphase2';
          max = -1;
          filters = 0;

          if (d.success) {
            results = $('.' + display);
            results.fadeIn();
            createtable('ReportsTable', th, checkbox, info, reports, submitvals, display, max, filters);
          } else {
            error.html(d.data.error);
          }
        }
      });
    }
  }
});