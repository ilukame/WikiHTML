

$(function(){
  $('li')
    .click(function(){
        let url_char = $(this).attr('data-char_url')
        if (url_char === "change1") document.right.location.href = "main.html";
        if (url_char === "change2") document.right.location.href = "main.html";
        if (url_char === "はじめに") document.right.location.href = "Pages/TOP/はじめに/はじめに.html";
    })
    .mouseover(function(){
      $(this).css('background', '#c00');
    })
    .mouseout(function(){
      $(this).css('background', 'white');
    });
});

