/* =========================================================
   CONFIGURAÇÕES E ELEMENTOS
========================================================= */

const pages = {
    inicio: [
        'Bem-vindo ao sistema RSA',
        'Escolha uma operação para começar.'
    ],
    chaves: [
        'Gerar chaves RSA',
        'Informe dois números primos para iniciar a geração.'
    ],
    criptografar: [
        'Criptografar mensagem',
        'Transforme uma mensagem em texto cifrado.'
    ],
    descriptografar: [
        'Descriptografar mensagem',
        'Recupere a mensagem original utilizando a chave privada.'
    ],
    sobre: [
        'Sobre o algoritmo RSA',
        'Entenda os conceitos por trás da criptografia assimétrica.'
    ]
};

const labels = {
    inicio: 'INÍCIO',
    chaves: 'GERAR CHAVES',
    criptografar: 'CRIPTOGRAFAR',
    descriptografar: 'DESCRIPTOGRAFAR',
    sobre: 'SOBRE O RSA'
};


/* =========================================================
   REFERÊNCIAS AOS ELEMENTOS HTML
========================================================= */

const keysPanel = document.getElementById('keys');
const toggleButton = document.getElementById('toggle');

const privateKey = document.getElementById('private');
const privateToggle = document.getElementById('toggle-private');
const privateStatus = document.getElementById('private-status');

const publicKey = document.getElementById('public');


/* =========================================================
   NAVEGAÇÃO ENTRE AS PÁGINAS
========================================================= */

function openPage(id) {
    if (!pages[id]) return;

    document.querySelectorAll('.page').forEach(page => {
        page.classList.toggle('show', page.id === id);
    });

    document.querySelectorAll('.nav').forEach(button => {
        button.classList.toggle(
            'active',
            button.dataset.page === id
        );
    });

    document.getElementById('title').textContent = pages[id][0];
    document.getElementById('subtitle').textContent = pages[id][1];
    document.getElementById('crumb').textContent = labels[id];
}

document.querySelectorAll('.nav[data-page]').forEach(button => {
    button.addEventListener('click', () => {
        openPage(button.dataset.page);
    });
});

document.querySelectorAll('[data-open]').forEach(button => {
    button.addEventListener('click', () => {
        openPage(button.dataset.open);
    });
});


/* =========================================================
   RECOLHER E EXPANDIR PAINEL DE CHAVES
========================================================= */

toggleButton.addEventListener('click', () => {
    keysPanel.classList.toggle('collapsed');

    const collapsed = keysPanel.classList.contains('collapsed');

    toggleButton.textContent = collapsed ? '›' : '⌄';

    toggleButton.setAttribute(
        'aria-label',
        collapsed ? 'Expandir painel' : 'Recolher painel'
    );
});


/* =========================================================
   SISTEMA DE NOTIFICAÇÕES
========================================================= */

let toastTimer;

function toast(message) {
    const toastElement = document.getElementById('toast');

    toastElement.textContent = message;
    toastElement.classList.add('show');

    clearTimeout(toastTimer);

    toastTimer = setTimeout(() => {
        toastElement.classList.remove('show');
    }, 2300);
}


/* =========================================================
   VARIÁVEIS DAS CHAVES RSA
========================================================= */

let privatePassword = null;
let privateVisible = false;
let privateValue = '';

let rsaKeysGenerated = false;
let publicExponent = null;
let modulus = null;
let privateExponent = null;


/* =========================================================
   PROTEÇÃO DA CHAVE PRIVADA
========================================================= */

function hidePrivateKey() {
    privateKey.textContent = '••••••••••••••••';

    privateVisible = false;

    privateStatus.textContent = 'Chave privada protegida.';

    privateToggle.setAttribute(
        'aria-label',
        'Exibir chave privada'
    );
}

function configurePrivatePassword() {
    const password = prompt(
        'Defina uma senha para proteger sua chave privada:'
    );

    if (!password || !password.trim()) {
        toast('Senha não definida.');
        return false;
    }

    privatePassword = password;

    toast('Senha da chave privada configurada.');

    return true;
}

privateToggle.addEventListener('click', () => {

    if (!privateValue) {
        toast('Gere as chaves RSA primeiro.');
        return;
    }

    // Se a chave estiver visível, basta ocultá-la.
    if (privateVisible) {
        hidePrivateKey();
        return;
    }

    // Primeira utilização: cadastrar a senha.
    if (!privatePassword) {

        if (!configurePrivatePassword()) {
            return;
        }

        privateKey.textContent = privateValue;

        privateVisible = true;

        privateStatus.textContent = 'Chave privada visível.';

        privateToggle.setAttribute(
            'aria-label',
            'Ocultar chave privada'
        );

        return;
    }

    // Próximas utilizações: solicitar a senha.
    const password = prompt(
        'Digite a senha para visualizar a chave privada:'
    );

    if (password !== privatePassword) {
        toast('Senha incorreta.');
        return;
    }

    privateKey.textContent = privateValue;

    privateVisible = true;

    privateStatus.textContent = 'Chave privada visível.';

    privateToggle.setAttribute(
        'aria-label',
        'Ocultar chave privada'
    );
});


/* =========================================================
   GERAÇÃO DE CHAVES RSA
========================================================= */

document.getElementById('gerar').addEventListener('click', () => {

    const p = document.getElementById('p').value.trim();
    const q = document.getElementById('q').value.trim();
    const e = document.getElementById('e').value.trim();

    if (!p || !q || !e) {
        toast('Informe os valores de p, q e e.');
        return;
    }

    if (Number(p) === Number(q)) {
        toast('Os números primos devem ser diferentes.');
        return;
    }

    fetch("http://127.0.0.1:5000/gerar-chaves", {
    method: "POST",
    headers: {
        "Content-Type": "application/json"
    },
    body: JSON.stringify({
        p: p,
        q: q,
        e: e
    })
})

    .then(resposta => resposta.json())
    .then(dados => {
        console.log(dados);

        publicExponent = dados.e;
        modulus = dados.n;
        privateExponent = dados.d;

        publicKey.textContent = `(${dados.e}, ${dados.n})`;

        privateValue = `(${dados.d}, ${dados.n})`;

        document.getElementById('key-result').textContent =
            `Chaves geradas com sucesso! Chave pública: (${dados.e}, ${dados.n})`;

        rsaKeysGenerated = true;

        hidePrivateKey();
    });
})

    /*
       DEMONSTRAÇÃO TEMPORÁRIA

       Estes valores são fixos e não são calculados
       a partir dos números informados pelo usuário.

       Na integração, esta parte será substituída
       pela resposta do programa RSA em C.
    */

   /*
   const publicDemo = '(17, 3233)';
    const privateDemo = '(2753, 3233)';

    publicKey.textContent = publicDemo;

    privateValue = privateDemo;

    rsaKeysGenerated = true;

    hidePrivateKey();

    document.getElementById('key-result').textContent =
        'Par de chaves demonstrativo gerado com sucesso.';

    toast('Par de chaves demonstrativo gerado!');
});
*/


/* =========================================================
   CRIPTOGRAFAR MENSAGEM
========================================================= */

document.getElementById('encrypt').addEventListener('click', () => {

    const message = document.getElementById('message').value.trim();

    if (!message) {
        toast('Digite uma mensagem para criptografar.');
        return;
    }

    if (!rsaKeysGenerated) {
        toast('Gere as chaves RSA primeiro.');
        return;
    }

    /*
       PONTO DE INTEGRAÇÃO COM C

       A mensagem será enviada ao algoritmo RSA em C.
       O resultado retornado deverá ser apresentado
       no elemento cipher-result.
    */

    fetch("http://127.0.0.1:5000/criptografar", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({
            mensagem: message,
            e: publicExponent,
            n: modulus
        })
    })

    .then(resposta => resposta.json())
    .then(dados => {
    console.log(dados);

        document.getElementById('cipher-result').textContent = dados.cifra.join(' ');

    });
});


/* =========================================================
   DESCRIPTOGRAFAR MENSAGEM
========================================================= */

document.getElementById('decrypt').addEventListener('click', () => {

    const cipher = document.getElementById('cipher').value.trim();

    if (!cipher) {
        toast('Informe o texto criptografado.');
        return;
    }

    if (!rsaKeysGenerated) {
        toast('Gere as chaves RSA primeiro.');
        return;
    }

    /*
       PONTO DE INTEGRAÇÃO COM C

       O texto cifrado será enviado ao algoritmo RSA em C.
       A mensagem recuperada será apresentada
       no elemento plain-result.
    */

   fetch("http://127.0.0.1:5000/descriptografar", {
    method: "POST",
    headers: {
        "Content-Type": "application/json"
    },
    body: JSON.stringify({
        cifra: cipher,
        d: privateExponent,
        n: modulus
    })
})

    .then(resposta => resposta.json())
    .then(dados => {
    console.log(dados);
    document.getElementById('plain-result').textContent = dados.mensagem;
});

});


/* =========================================================
   COPIAR CHAVES
========================================================= */

document.querySelectorAll('[data-copy]').forEach(button => {

    button.addEventListener('click', async () => {

        const elementId = button.dataset.copy;

        const element = document.getElementById(elementId);

        const value = element.textContent.trim();

        // Impede copiar a chave privada enquanto estiver oculta.
        if (elementId === 'private' && !privateVisible) {
            toast('Visualize a chave privada com sua senha antes de copiar.');
            return;
        }

        if (
            value === 'Ainda não gerada' ||
            !value ||
            value === '••••••••••••••••'
        ) {
            toast('Nenhuma chave disponível para copiar.');
            return;
        }

        try {
            await navigator.clipboard.writeText(value);

            toast('Chave copiada.');

        } catch (error) {
            toast('Não foi possível copiar neste navegador.');
        }
    });

});


/* =========================================================
   INICIALIZAÇÃO
========================================================= */

// Mantém a chave privada protegida ao carregar a página.
hidePrivateKey();

// Inicia o sistema na página inicial.
openPage('inicio');