

function ClickUrl() {
  alert("子");
}

$(function(){
  $('li').click(function(){
      let url_char = $(this).attr('data-char')
      //alert(url_char);
      //alert(window.parent.location.href);
      window.parent.ParentTest();
  });
});