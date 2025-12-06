data class Op(
  val op: (Long, Long) -> Long,
  val length: Int,
)

fun main() {
  val allLines = generateSequence(::readLine).toList()
  val numLines = allLines.dropLast(1)
  val nums = 
  (0..<numLines[0].length).mapNotNull { i ->
    val numStr = numLines.map { it[i] }.joinToString("").trim()
    if (numStr.isEmpty()) null else numStr.toLong()
  }

  // last column doesn't have a blank column after it, adding a space to make calculations
  // uniform below
  val opsLine = allLines.last() + " "

  val ops = 
    """[+*]\s+""".toRegex().findAll(opsLine).map {
      val opFun: (Long, Long) -> Long = if (it.value[0] == '*') {
          Long::times
        } else {
          require(it.value[0] == '+')
          Long::plus
        }
      Op(
        op = opFun,
        // number of spaces is how many numbers we need
        length = it.value.length - 1
      )
    }.toList()
  var start = 0
  var total = 0L
  for (op in ops) {
    val end = start + op.length
    total += nums.subList(start, end).reduce(op.op)
    start = end
  }
  println(total)
}
