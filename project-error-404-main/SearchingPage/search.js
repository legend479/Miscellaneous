const container = document.querySelector('.container');
const artistImage = document.querySelector('.artist');
const media = document.querySelector('.media');
const overlay = document.querySelector('.overlay');
const searchElem = document.querySelector('#search');

const getContent = (search, explicit, duration) => {
  const url = new URL(`https://itunes.apple.com/search?term=${search}&entity=song`);
  fetch(url)
    .then(results => results.json())
    .then(data => {
      resultsof = data.results;
    index=0
    resultsHTML=""
    if (explicit==="0")
    {
        for (var i = 0; i < resultsof.length; i++) {
            if (Number(resultsof[i].trackTimeMillis)<=Number(duration))
            {
                if (resultsof[i].trackExplicitness=="explicit")
                {resultsof[i].trackName= resultsof[i].trackName.replace(/'/g, '&quot');
                const num = `
                <div class="result">
                    <div>
                        <img src="${(resultsof[i]).artworkUrl100}">
                    </div>
                    <div class="contentsofartist">${resultsof[i].trackName}<img src="./Explicit.png" height=20vh width=20vw style="background:white; border-color: white; border-radius:200%; border-width: 100px; margin-left:1vw">
                    </div>
                    <div class="contentsofartists">
                    <p>Arist: ${resultsof[i].artistName}</p>
                    <p>${Math.floor(resultsof[i].trackTimeMillis/60000)}m ${Math.floor(resultsof[i].trackTimeMillis%60000/1000)}s</p>
                    </div>
                    <div class="contentsofartist">
                    <img src="./PlayButton.png" width=40vw height=40vh onclick="openMedia('${resultsof[i].previewUrl}','${resultsof[i].trackName}')">
                    </div>
                </div>
        
                `
                resultsHTML+=num;
                index++;
                }
                else
                {
                    resultsof[i].trackName= resultsof[i].trackName.replace(/'/g, '&quot');
                const num = `
                <div class="result">
                    <div>
                        <img src="${(resultsof[i]).artworkUrl100}">
                    </div>
                    <div class="contentsofartist">${resultsof[i].trackName}
                    </div>
                    <div class="contentsofartists">
                    <p>Arist: ${resultsof[i].artistName}</p>
                    <p>${Math.floor(resultsof[i].trackTimeMillis/60000)}m ${Math.floor(resultsof[i].trackTimeMillis%60000/1000)}s</p>
                    </div>
                    <div class="contentsofartist">
                    <img src="./PlayButton.png" width=40vw height=40vh onclick="openMedia('${resultsof[i].previewUrl}','${resultsof[i].trackName}')">
                    </div>
                </div>
                `
                resultsHTML+=num;
                index++;
                }
            }
            if (index==10)
            {
                break;
            }
        }
        if (index==0)
        {
            resultsHTML=`<div style=" position:absolute;top:40vh; left:42vw; text-align: center; font-size: 10vh;">No Results Found!</div>`
        }
    }
    if (explicit==="2")
    {
        for (var i = 0; i < resultsof.length; i++) {
            if (resultsof[i].trackExplicitness==="notExplicit"&&Number(resultsof[i].trackTimeMillis)<=Number(duration))
            {
                resultsof[i].trackName= resultsof[i].trackName.replace(/'/g, '&quot');
            const num = `
                <div class="result">
                    <div>
                        <img src="${(resultsof[i]).artworkUrl100}">
                    </div>
                    <div class="contentsofartist">${resultsof[i].trackName}
                    </div>
                    <div class="contentsofartists">
                    <p>Arist: ${resultsof[i].artistName}</p>
                    <p>${Math.floor(resultsof[i].trackTimeMillis/60000)}m ${Math.floor(resultsof[i].trackTimeMillis%60000/1000)}s</p>
                    </div>
                    <div class="contentsofartist">
                    <img src="./PlayButton.png" width=40vw height=40vh onclick="openMedia('${resultsof[i].previewUrl}','${resultsof[i].trackName}')">
                    </div>
                </div>
        
                `
                resultsHTML+=num;
                index++;
            }
            if (index==10)
            {
                break;
            }
        }
        if (index==0)
        {
            resultsHTML=`<div style=" position:absolute;top:40vh; left:42vw; text-align: center; font-size: 10vh;">No Results Found!</div>`
        }
    }
    if (explicit==="1")
    {
        for (var i = 0; i < resultsof.length; i++) {
            if (resultsof[i].trackExplicitness==="explicit"&&Number(resultsof[i].trackTimeMillis)<=Number(duration))
            {
                resultsof[i].trackName= resultsof[i].trackName.replace(/'/g, '&quot');
            const num = `
                <div class="result">
                    <div>
                        <img src="${(resultsof[i]).artworkUrl100}">
                    </div>
                    <div class="contentsofartist">${resultsof[i].trackName}<img src="./Explicit.png" height=20vh width=20vw style="background:white; border-color: white; border-radius:200%; border-width: 100px; margin-left:1vw">
                    </div>
                    <div class="contentsofartists">
                    <p>Arist: ${resultsof[i].artistName}</p>
                    <p>${Math.floor(resultsof[i].trackTimeMillis/60000)}m ${Math.floor(resultsof[i].trackTimeMillis%60000/1000)}s</p>
                    </div>
                    <div class="contentsofartist">
                    <img src="./PlayButton.png" width=40vw height=40vh onclick="openMedia('${resultsof[i].previewUrl}','${resultsof[i].trackName}')">
                    </div>
                </div>
                `
                resultsHTML+=num;
                index++;
            }
            if (index==10)
            {
                break;
            }
        }
        if (index==0)
        {
            resultsHTML=`<div style=" position:absolute;top:40vh; left:42vw; text-align: center; font-size: 10vh;">No Results Found!</div>`
        }

    }
        container.innerHTML = resultsHTML;
        searchElem.blur();
        return fetch(resultsof[0].artistViewUrl)
      })
      .then(data => data.text())
      .then(data => {
        const artistImgUrl = data.match(/https?:\/\/[a-zA-Z0-9:\/\.\-]+.jpg/)[0];
        artistImage.style['background-image'] = `url(${artistImgUrl})`;
      })

 }

const openMedia = (url, title) => {
  media.innerHTML = `<audio controls autoplay src="${url}" class="player"></audio><p>${title}</p>`;
//   document.querySelectorAll('.result').forEach(e => e.classList.add('blur'));
//   overlay.classList.add('blur');
  media.classList.remove('hidden');
  play=true;
}

const closeMedia = () => {
  media.innerHTML = '';
  toggleOverlay();
  media.classList.add('hidden');
}

const toggleOverlay = () => {
  document.querySelectorAll('.result').forEach(e => e.classList.toggle('blur'));
  overlay.classList.toggle('blur');

}

overlay.addEventListener('click', closeMedia);
searchElem.addEventListener('keydown', (event) => {
  if (event.key === 'Enter') {
    toggleOverlay();
    selectElement = document.querySelector('#select1');
    output = selectElement.value;
    durat= document.getElementById("Time").value;
    let duration
    if(durat!="")
    {
    let dur=durat;
    duration = dur*60000;
    }
    else
    {
        duration=100000000000;
    }
    getContent(event.target.value,output,duration);
    searchElem.blur();
  }
});

document.body.onkeyup = function(e) {
    if (e.key == " " ||
        e.code == "Space" ||      
        e.keyCode == 32      
    )
    {
        if (play) {
            document.getElementsByClassName("player")[0].pause();
            play = false;
        } else {
            document.getElementsByClassName("player")[0].play();
            play = true;
        }
    }
};

const getOption=() => {
    const searching = document.getElementById("search");
    selectElement = document.querySelector('#select1');
    output = selectElement.value;
    durat= document.getElementById("Time").value;
    let duration
    if(durat!="")
    {
    let dur=durat;
    duration = dur*60000;
    }
    else
    {
        duration=100000000000;
    }
    getContent(searching.value ,output,duration);
    searchElem.blur();
}

const clearoptions=() =>{
    document.getElementById("select1").value="0";
    document.getElementById("Time").value="";
}
searchElem.addEventListener('focus', toggleOverlay);

var color;
var BGC;
function HoverOn(a) {
    color = a.style.color;
    BGC = a.style.backgroundColor;
    a.style.color = "#aaa";
    a.style.backgroundColor = "black";
}
function HoverOff(a) {
    a.style.color = color;
    a.style.backgroundColor = BGC;
}

const text = "#Suggesting U Songs#";
let index = 0;
let isTyping = false;

function type() {
    document.getElementById("WebName").innerHTML += text.charAt(index);
    index++;
    if (index >= text.length) {
        clearInterval(interval);
    }
}

const observer = new IntersectionObserver(entries => {
    if (entries[0].isIntersecting && !isTyping) {
        isTyping = true;
        const interval = setInterval(type, 100);
        document.getElementById("WebName").style.opacity = 1;
    }
});
observer.observe(document.getElementById("WebName"));