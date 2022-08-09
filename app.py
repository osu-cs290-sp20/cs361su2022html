import requests
import json
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity
from flask import Flask, request, jsonify

app = Flask(__name__)

resume_arr = [{"id": 0, "resume": "blank", "job": "blank"}]
percent_arr = [{"id": 0, "percent": 0.0}]

#input: id of case
#output: json object with id and percent similarity between resume and job description
def get_percent(idx):
    arr = [resume_arr[idx]["resume"], resume_arr[idx]["job"]]
    cv = CountVectorizer()
    matrix = cv.fit_transform(arr)

    percent = cosine_similarity(matrix)[0][1] * 100
    percent = round(percent, 1)
    print(percent)
    percent_arr.append({"id": idx, "percent": percent})
    return jsonify(id = idx, percent = percent)


#returns either specific case id and percent or all cases and percents
@app.get("/api/resumes")
def get_api():
    if request.args:
        args = request.args
        if args.get("id", default = "", type=int) >= len(percent_arr):
            return jsonify(alert = "This case does not seem to exist, please enter a valid ID")
        return get_percent(args.get("id", default = "", type=int)), 200
    else:
        return json.dumps(percent_arr), 200

#adds info from post request to resume_arr and percent_arr and returns percent match and case id
@app.post("/api/resumes")
def send_percent():
    if request.is_json:
        resume = request.get_json()
        resume["id"] = len(resume_arr)
        resume_arr.append(resume)
        percent = get_percent(resume["id"])
        return percent, 200
    else:
        resume = {"id": -1, "resume": "", "job": ""}
        resume["id"] = len(resume_arr)
        resume["resume"] = request.form.get("resume")
        resume["job"] = request.form.get("job")
        resume_arr.append(resume)
        percent = get_percent(resume["id"])
        return percent, 200