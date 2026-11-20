from flask import Flask, request, jsonify
from flask_cors import CORS
import subprocess

app = Flask(__name__)
CORS(app)

@app.route("/gerar-chaves", methods = ["POST"])
def gerar_chaves():
    dados =  request.get_json()
    p = dados["p"]
    q = dados["q"]
    e = dados["e"]

    lista = ["rsa/output/criptografia_RSA.exe", str(p), str(q), str(e)]

    resultado = subprocess.run(lista, capture_output = True, text = True)

    if resultado.returncode != 0:
        return jsonify({"erro": resultado.stderr}), 400

    chaves_geradas = resultado.stdout.strip().split()

    n = int(chaves_geradas[0])
    e_publico = int(chaves_geradas[1])
    d = int(chaves_geradas[2])


    print("Dados recebidos:", p, q, e)

    return jsonify({
        "n": n,
        "e": e_publico,
        "d": d
    })

@app.route("/criptografar", methods = ["POST"])
def criptografar():
    cripto =  request.get_json()
    mensagem = cripto["mensagem"]
    e = cripto["e"]
    n = cripto["n"]

    lista2 = ["rsa/output/criptografia_RSA.exe", "criptografar", mensagem, str(e),str(n)]

    resultado2 = subprocess.run(lista2, capture_output = True, text = True)

    if resultado2.returncode != 0:
            return jsonify({"erro": resultado2.stderr}), 400

    criptografados = resultado2.stdout.strip().split()
    
    criptografados = [int(numero) for numero in criptografados]

    return jsonify({
        "cifra": criptografados
    })

@app.route("/descriptografar", methods = ["POST"])
def descriptografar():
    descripto = request.get_json()
    cifra = descripto["cifra"]
    d = descripto["d"]
    n = descripto["n"]

    lista3 =["rsa/output/criptografia_RSA.exe", "descriptografar", cifra, str(d), str(n)]

    resultado3 = subprocess.run(lista3, capture_output = True, text = True)

    if resultado3.returncode != 0:
                return jsonify({"erro": resultado3.stderr}), 400

    mensagem_recuperada = resultado3.stdout.strip()

    return jsonify({
        "mensagem": mensagem_recuperada
    })

@app.route("/")
def inicio():
    return "Servidor RSA funcionando!"

if __name__ == "__main__":
    app.run(debug = True)