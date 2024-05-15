# @param {String[]} words
# @param {String} s
# @return {Boolean}
def is_acronym(words, s)
  if words.size != s.size
      return false
  end
  for i in 0...words.size
      if words[i][0] != s[i]
          return false
      end
  end
  true
end
