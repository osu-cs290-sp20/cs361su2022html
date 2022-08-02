import requests
import json
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity
from flask import Flask, request, jsonify

app = Flask(__name__)

resume_arr = [{"id": 0, "resume": "blank", "job": "blank"}]
percent_arr = [{"id": 0, "percent": 0.0}]

def get_percent(idx):
    arr = [resume_arr[idx]["resume"], resume_arr[idx]["job"]]
    c = CountVectorizer()
    matrix = c.fit_transform(arr)

    percent = cosine_similarity(matrix)[0][1] * 100
    percent = round(percent, 1)
    print(percent)
    return jsonify(id = idx, percent = percent)


@app.get("/api/resumes")
def get_api():
    args = request.args
    return get_percent(args.get("id", default = "", type=int))

@app.post("/api/resumes")
def send_percent():
    if request.is_json:
        resume = request.get_json()
        resume["id"] = len(resume_arr)
        resume_arr.append(resume)
        percent = get_percent(resume["id"])
        return percent, 200
    return