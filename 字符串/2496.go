func maximumValue(strs []string) int {
    n := len(strs)
    var cal func(string) int
    cal = func(s string) int {
        regex := regexp.MustCompile("[a-z]")
        if regex.MatchString(s) {
            return len(s)
        }
        num, _ := strconv.Atoi(s)
        return num
    }
    res := 0
    for i := 0; i < n; i++ {
        value := cal(strs[i])
        if res < value {
            res = value
        }
    }
    return res
}

// func max(a int, b int) int {
//     if a > b {
//         return a
//     }
//     return b
// }

// func maximumValue(strs []string) int {
//     res := 0
//     for _, s := range strs {
//         isDigits := true
//         for _, c := range s {
//             isDigits = isDigits && (c >= '0' && c <= '9')
//         }
//         if isDigits {
//             v, _ := strconv.Atoi(s)
//             res = max(res, v)
//         } else {
//             res = max(res, len(s))
//         }
//     }
//     return res
// }
