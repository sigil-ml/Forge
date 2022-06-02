#!/bin/bash

WEBHOOK="https://discord.com/api/webhooks/962049385968046150/SUler34IVX_0vpgS6xmslF4DDTA6K_g60R7n0IedJDBkBiYZuiIoKedUVRR2xNyYwLfZ"
PAT="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"

# Auto Formatting
format_code () {
  python3 commit_pipeline/black_formatter.py
}

# Auto Documentation
auto_document () {
  touch sphinx_logs.txt
  make html > sphinx_logs.txt
# cp -r docs/_build/html docs/
}

snyk_vuln () {
  touch snyk_logs.txt
  pip3 install -r src/requirements.txt
  snyk test --file=src/requirements.txt --command=python3 > snyk_logs.txt
}

notify_detailed () {
  black_file=`echo black_logs.txt | python3 commit_pipeline/clean_text.py`
  sphinx_file=`echo sphinx_logs.txt | python3 commit_pipeline/clean_text.py`
  # snyk_file=`echo snyk_logs.txt | python3 commit_pipeline/clean_text.py`
  # --field "Snyk;$snyk_file" \


  ./discord.sh \
  --webhook-url="$WEBHOOK" \
  --username "CI Pipeline" \
  --avatar "" \
  --text "$1" \
  --title "Pipeline Notification" \
  --description "\nCommit Msg:\n $CMT_MSG \n\n $4" \
  --color "$2" \
  --author "Andrew Romans" \
  --author-url "" \
  --author-icon "" \
  --image "" \
  --thumbnail "$3" \
  --field "Black;$black_file" \
  --field "Sphinx;$sphinx_file" \
  --footer "CommitPipeline" \
  --timestamp
}

notify_simple () {
  ./discord.sh --webhook-url="$WEBHOOK" --text "$1"
}

# Commit Code
git_commit () {
  git config --global --add safe.directory /home/AI-CI
  git config --global user.email "github.sigil.ai@gmail.com"
  git config --global user.name "Sigil Bot"
  git add .
  git commit -m "$1"
  git push https://sigilbot:${PAT}@github.com/sigil-ml/AI-CI.git
}

# snyk_vuln && \
{ #try 

  format_code && \ 
  auto_document && \ 
  notify_simple "Commit pipeline succesful!" && \
  git_commit "$CMT_MSG"

  last_commit=`git log | grep -oE "\W.{40,}" -m 1 | xargs`
  git_link="https://github.com/sigil-ml/AI-CI/commit/$last_commit"

  notify_detailed "Commit details" "0x2dcc70" "https://imgur.com/zBVXXdd.png" $git_link

} || { #except

  notify_detailed "Build Failed!" "0xf44236" "https://cdn-icons-png.flaticon.com/512/1828/1828843.png" ""

}

